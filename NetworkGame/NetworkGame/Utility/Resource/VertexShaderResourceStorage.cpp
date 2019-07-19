#include "VertexShaderResourceStorage.h"
#include "Utility/Debug.h"
#include "Utility/Render/DXFunc.h"
#include "Device/GameDevice.h"
#include "Device/Graphics/GraphicsDeviceManager.h"

namespace Utility {

VertexShaderResourceStorage::VertexShaderResourceStorage() {}

VertexShaderResourceStorage::~VertexShaderResourceStorage() {}

void VertexShaderResourceStorage::importResource(Define::VertexShaderType type, const std::string& filepath) {
    if (exist(type))return;
    mResources[type] = std::make_shared<Graphics::VertexShader>(
        Device::GameDevice::getInstance().getDirectX11Device(), filepath);
}
} //Utility 
