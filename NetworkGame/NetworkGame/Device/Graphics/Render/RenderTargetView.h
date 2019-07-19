#pragma once

#include <memory>
#include <wrl/client.h>
#include <d3d11.h>

namespace Graphics {

class Color4;
class GraphicsDeviceManager;
class TextureBuffer;
class Texture;

class RenderTargetView {
    using TexBufferPtr = std::shared_ptr<TextureBuffer>;
public:
    RenderTargetView(GraphicsDeviceManager& graphicsDevice,
        TexBufferPtr targetTexture, bool createTexture = true);
    ~RenderTargetView();
    TexBufferPtr getTargetTexture() const { return mTargetTexture; }
    Texture& getRenderTargetTexture() { return *mRenderTargetTexture; }
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> getRenderTargetView() const { return mRenderTargetView; }
    void clear(const Color4& color);
private:
    GraphicsDeviceManager& mGraphicsDevice;
    TexBufferPtr mTargetTexture;
    std::unique_ptr<Texture> mRenderTargetTexture;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
};

} //Graphics 