#include "RenderTargetFactory.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Texture/TextureBuffer.h"
#include "Device/Graphics/Render/RenderTargetView.h"
#include "Device/Graphics/Render/Viewport.h"
#include "Device/Graphics/Render/RenderTarget.h"
#include "Device/Graphics/Render/DepthStencilView.h"

namespace Graphics {

RenderTargetFactory::RenderTargetFactory(GraphicsDeviceManager& graphicsDevice)
    :mGraphicsDevice(graphicsDevice) {
    memset(&mDesc, 0, sizeof(mDesc));
    mDesc.Usage = D3D11_USAGE_DEFAULT;
    mDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
    mDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    mDesc.CPUAccessFlags = 0;
    mDesc.MipLevels = 1;
    mDesc.ArraySize = 1;
    mDesc.SampleDesc.Count = 1;
    mDesc.SampleDesc.Quality = 0;
}

RenderTargetFactory::~RenderTargetFactory() {}

std::unique_ptr<RenderTarget> RenderTargetFactory::createRenderTarget(int viewNum, const Math::Vector2& size) {
    return createRenderTarget(viewNum, size, nullptr);
}

std::unique_ptr<RenderTarget> RenderTargetFactory::createRenderTarget(int viewNum, const Math::Vector2 & size, std::unique_ptr<DepthStencilView> depthStencil) {
    mDesc.Width = (UINT)size.x;
    mDesc.Height = (UINT)size.y;

    std::unique_ptr<TextureBuffer> texBuffer = std::make_unique<TextureBuffer>(mGraphicsDevice.getDirectX11Device(), mDesc);
    std::unique_ptr<RenderTargetView> view = std::make_unique<RenderTargetView>(mGraphicsDevice, std::move(texBuffer));
    Viewport viewport(size);
    std::unique_ptr<RenderTarget> result =
        std::make_unique<RenderTarget>(mGraphicsDevice.getDirectX11Device(), viewport, std::move(view), std::move(depthStencil));
    for (int i = 0; i < viewNum - 1; i++) {
        texBuffer = std::make_unique<TextureBuffer>(mGraphicsDevice.getDirectX11Device(), mDesc);
        view = std::make_unique<RenderTargetView>(mGraphicsDevice, std::move(texBuffer));
        result->addRenderTarget(std::move(view));
    }

    return result;
}

} //Graphics 
