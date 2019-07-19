#pragma once

#include <vector>
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include "Utility/Math/Vector2.h"
#include "Device/Graphics/Color4.h"

namespace Graphics {

class DirectX11GraphicsDevice;
class Viewport;
class DepthStencilView;
class RenderTargetView;

class RenderTarget {
public:
    RenderTarget(DirectX11GraphicsDevice& graphicsDevice,
        const Viewport& viewport,
        std::unique_ptr<RenderTargetView> renderTargetView,
        std::unique_ptr<DepthStencilView> depthStencil = nullptr,
        const Color4& clearColor = Color4(0.0f, 0.0f, 0.0f, 0.0f));
    ~RenderTarget();
    void addViewPort(const Viewport& viewport);
    void addRenderTarget(std::unique_ptr<RenderTargetView> renderTargetView);
    RenderTargetView& getRenderTargetView(int id);
    void activate();
    Math::Vector2 getViewPortSize(int id);
    void clear();
private:
    DirectX11GraphicsDevice& mGraphicsDevice;
    std::vector<Viewport> mViewPorts;
    std::vector<std::unique_ptr<RenderTargetView>> mRenderTargetView;
    std::unique_ptr<DepthStencilView> mDepthStencil;
    Color4 mClearColor;
};

} //Graphics 