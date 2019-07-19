#include "LightManager.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/GraphicsDeviceManager.h"

namespace Graphics {

LightManager::LightManager(GraphicsDeviceManager& device)
    :mDevice(device) {}

LightManager::~LightManager() {}

int LightManager::addLight(const PointLightParam& param) {
    mPointLights.emplace_back(std::make_unique<PointLight>(param));
    return mPointLights.size() - 1;
}
int LightManager::addLight(const DirectionalLightParam & param) {
    mDirectionalLights.emplace_back(std::make_unique<DirectionalLight>(param));
    return mDirectionalLights.size() - 1;
}
void LightManager::set() {
    ConstantBufferManager& cbManager = mDevice.getConstantBufferManager();
    LightingCBufferStruct buffer;

    UINT cnt = 0;
    for (auto&& dirLight : mDirectionalLights) {
        if (!dirLight->isActive())continue;
        dirLight->setParamToBuffer(&buffer.dirLights[cnt]);
        cnt++;
        MY_ASSERTION(cnt <= Define::LightSettings::DIRECTIONALLIGHT_NUM,
            "ディレクショナルライトの配置限界量を超えています。");
    }

    cnt = 0;
    for (auto&& pLight : mPointLights) {
        if (!pLight->isActive())continue;
        pLight->setParamToBuffer(&buffer.pLights[cnt]);
        cnt++;
        MY_ASSERTION(cnt <= Define::LightSettings::POINTLIGHT_NUM,
            "ポイントライトの配置限界量を超えています。");
    }
    cbManager.setStruct(buffer);
}

} //Graphics 
