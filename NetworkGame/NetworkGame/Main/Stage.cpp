#include "Stage.h"
#include "Device/Graphics/Model/Model.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Device/GameDevice.h"
#include "Define/Resource/Model.h"
#include "Utility/Resource/ResourceManager.h"

#include "Device/Input/Mouse.h"
#include "Device/Input/InputManager.h"
#include "Define/Path.h"
#include <iostream>

namespace Main {

Stage::Stage()
    :mFloorTransform(Math::Vector3(0, 0, 0), Math::Quaternion(), Math::Vector3(100.0f, 1.0f, 100.0f)),
    mObjectColor(Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f)),
    mFloorPlane(Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f)) {
    Graphics::FBXLoader loader(Device::GameDevice::getInstance().getDirectX11Device());
    mFloor = loader.load(Define::ModelName::FLOOR_NAME);
    Utility::PixelShaderResourceStorage* psManager = Utility::ResourceManager::getInstance().getPixelShader();
    mObjectModel = loader.load(Define::ModelName::OBJECT_NAME);
    mObjectModel->setPixelShader(psManager->getResource(Define::PixelShaderType::NoTextureNoLighting));

    mObjectTransforms.emplace_back(Math::Vector3(0.0f, 2.5f, 0.0f), Math::Quaternion(), Math::Vector3(1.0f, 1.0f, 1.0f));
    mObjectTransforms.emplace_back(Math::Vector3(5.0f, 2.5f, 0.0f), Math::Quaternion(), Math::Vector3(1.0f, 1.0f, 1.0f));
}


Stage::~Stage() {}

void Stage::update(float delta) {}

void Stage::draw() {
    mFloor->draw(mFloorTransform);
    Graphics::ConstantBufferManager& cbManager = Device::GameDevice::getInstance().getDirectX11Device().getConstantBufferManager();
    cbManager.setColor(Graphics::ConstantBufferParameterType::Color, mObjectColor);

    //オブジェクトの数分描画する
    for (auto&& tr : mObjectTransforms) {
        mObjectModel->draw(tr);
    }
}

} //Main 
