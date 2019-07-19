#include "PostEffect.h"
#include "Device/Graphics/Shader/VertexShader.h"
#include "Device/Graphics/Shader/PixelShader.h"
#include "Device/Graphics/Render/RenderTarget.h"

namespace Graphics {

PostEffect::PostEffect(std::shared_ptr<VertexShader> vshader,
    std::shared_ptr<PixelShader> pshader,
    std::unique_ptr<RenderTarget> rt)
    :mVShader(vshader), mPShader(pshader), mRenderTarget(std::move(rt)) {}

PostEffect::~PostEffect() {}

RenderTarget& PostEffect::set() {
    mRenderTarget->activate();
    mVShader->set();
    mPShader->set();
    return *mRenderTarget;
}

} //Graphics 
