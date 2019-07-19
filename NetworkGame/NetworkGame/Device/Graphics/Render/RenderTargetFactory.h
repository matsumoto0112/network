#pragma once

#include <memory>
#include <d3d11.h>
#include "Utility/Math/Vector2.h"

namespace Graphics {

class RenderTarget;
class GraphicsDeviceManager;
class DepthStencilView;

class RenderTargetFactory {
public:
    RenderTargetFactory(GraphicsDeviceManager& graphicsDevice);
    ~RenderTargetFactory();
    std::unique_ptr<RenderTarget> createRenderTarget(int viewNum, const Math::Vector2& size);
    std::unique_ptr<RenderTarget> createRenderTarget(int viewNum, const Math::Vector2& size, std::unique_ptr<DepthStencilView> depthStencil);
private:
    GraphicsDeviceManager& mGraphicsDevice;
    D3D11_TEXTURE2D_DESC mDesc;
};

} //Graphics 