#include "PixelShaderResourceStorage.h"
#include "Device/GameDevice.h"

namespace Utility {

PixelShaderResourceStorage::PixelShaderResourceStorage() {}

PixelShaderResourceStorage::~PixelShaderResourceStorage() {}

void PixelShaderResourceStorage::importResource(Define::PixelShaderType type, const std::string& filepath) {
    if (exist(type))return;
    mResources.emplace(type,
        std::make_shared<Graphics::PixelShader>(Device::GameDevice::getInstance().getDirectX11Device(), filepath));
}
} //Utility 
