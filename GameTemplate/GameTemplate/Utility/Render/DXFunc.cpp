#include "DXFunc.h"
#include "Device/GameDevice.h"
#include "Device/Graphics/GraphicsDeviceManager.h"

namespace Utility {

ID3D11Device* getDevice() {
    return Device::GameDevice::getInstance().getDirectX11Device().getDevice().Get();
}

ID3D11DeviceContext* getContext() {
    return Device::GameDevice::getInstance().getDirectX11Device().getContext().Get();
}

} //Utility 
