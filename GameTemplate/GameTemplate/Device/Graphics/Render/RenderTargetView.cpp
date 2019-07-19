#include "RenderTargetView.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Utility/Debug.h"
#include "Device/Graphics/Texture/Texture.h"
#include "Device/Graphics/Texture/TextureBuffer.h"
#include "Device/Graphics/Shader/ShaderResourceView.h"

namespace Graphics {

RenderTargetView::RenderTargetView(GraphicsDeviceManager& graphicsDevice,
    TexBufferPtr targetTexture, bool createTexture)
    :mGraphicsDevice(graphicsDevice), mTargetTexture(targetTexture) {
    D3D11_RENDER_TARGET_VIEW_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    HRESULT hr = graphicsDevice.getDevice()->CreateRenderTargetView(
        mTargetTexture->getBuffer().Get(), &desc, &mRenderTargetView);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "RTVì¬¸”s");
        return;
    }

    if (!createTexture)return;
    std::shared_ptr<ShaderResourceView> srv2 =
        std::make_shared<ShaderResourceView>(graphicsDevice.getDirectX11Device(), *targetTexture);

    Math::Vector2 size = targetTexture->getSize();
    mRenderTargetTexture = std::make_unique<Texture>(graphicsDevice,
        targetTexture, srv2, (int)size.x, (int)size.y);
}

RenderTargetView::~RenderTargetView() {}

void RenderTargetView::clear(const Color4& color) {
    mGraphicsDevice.getContext()->ClearRenderTargetView(mRenderTargetView.Get(), color.get().data());
}

} //Graphics 
