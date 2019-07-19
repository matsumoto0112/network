#include "Texture.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Shader/ShaderInputType.h"
#include "Device/Graphics/Shader/ShaderResourceView.h"
#include "Utility/Debug.h"

namespace Graphics {

Texture::Texture(GraphicsDeviceManager& graphicsDevice,
    Texture2DPtr texture2D, SRVPtr srv, int width, int height)
    :mGraphicsDevice(graphicsDevice),
    mTexture2D(texture2D),
    mSRV(srv),
    mWidth(width),
    mHeight(height) {}

Texture::~Texture() {}

void Texture::setData(ShaderInputType inputType, UINT slotNum) const {
    switch (inputType) {
    case ShaderInputType::Vertex:
        mGraphicsDevice.getContext()->VSSetShaderResources(
            slotNum, 1, mSRV->getShaderResourceView().GetAddressOf());
        break;
    case ShaderInputType::Pixel:
        mGraphicsDevice.getContext()->PSSetShaderResources(
            slotNum, 1, mSRV->getShaderResourceView().GetAddressOf());
        break;
    default:
        MY_ASSERTION(false, "どちらかのシェーダーを選択してください。");
        break;
    }
}

int Texture::getWidth() const {
    return mWidth;
}

int Texture::getHeight() const {
    return mHeight;
}

} //Graphics 
