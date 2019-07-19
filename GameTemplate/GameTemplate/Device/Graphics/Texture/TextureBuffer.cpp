#include "TextureBuffer.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"
#include "Utility/Debug.h"

namespace Graphics {

Graphics::TextureBuffer::TextureBuffer(DirectX11GraphicsDevice& graphicsDevice) {
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = graphicsDevice.getSwapChain();
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&mTextureBuffer);
    D3D11_TEXTURE2D_DESC desc;
    mTextureBuffer->GetDesc(&desc);
    mSize.x = (float)desc.Width;
    mSize.y = (float)desc.Height;
}

TextureBuffer::TextureBuffer(DirectX11GraphicsDevice& graphicsDevice,
    const D3D11_TEXTURE2D_DESC& desc)
    :mSize((float)desc.Width, (float)desc.Height) {
    Microsoft::WRL::ComPtr<ID3D11Device> device = graphicsDevice.getDevice();
    HRESULT hr = device->CreateTexture2D(&desc, nullptr, &mTextureBuffer);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "テクスチャバッファの作成に失敗しました。");
    }
}

TextureBuffer::TextureBuffer(DirectX11GraphicsDevice& graphicsDevice,
    const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA& sub)
    :mSize((float)desc.Width, (float)desc.Height) {
    Microsoft::WRL::ComPtr<ID3D11Device> device = graphicsDevice.getDevice();
    HRESULT hr = device->CreateTexture2D(&desc, &sub, &mTextureBuffer);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "テクスチャバッファの作成に失敗しました。");
    }
}

Graphics::TextureBuffer::~TextureBuffer() {}

} //Graphics 
