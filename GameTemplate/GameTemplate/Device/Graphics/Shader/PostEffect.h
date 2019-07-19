#pragma once

#include <memory>

namespace Graphics {

class VertexShader;
class PixelShader;
class RenderTarget;

class PostEffect {
public:
    PostEffect(std::shared_ptr<VertexShader> vshader,
        std::shared_ptr<PixelShader> pshader,
        std::unique_ptr<RenderTarget> rt);
    ~PostEffect();
    RenderTarget& set();
private:
    std::shared_ptr<VertexShader> mVShader;
    std::shared_ptr<PixelShader> mPShader;
    std::unique_ptr<RenderTarget> mRenderTarget;
};

} //Graphics 