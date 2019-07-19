#include "Camera.h"
#include "Device/Graphics/Render/RenderTarget.h"
#include "Device/Graphics/Render/RenderTargetView.h"
#include "Device/Graphics/Texture/Texture.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/Shader/PostEffect.h"
#include "Device/Graphics/Primitive/Quad2D.h"
#include "Define/Window.h"

namespace Graphics {

Camera::Camera(GraphicsDeviceManager& graphicsDevice,
    std::unique_ptr<RenderTarget> renderTarget)
    :mGraphicsDevice(graphicsDevice),
    mRenderTarget(std::move(renderTarget)),
    mIsActive(true),
    mQuad(std::make_unique<Quad2D>(graphicsDevice,
        Math::AABB2D(Math::Vector2(0.0f, 0.0f), Math::Vector2(mRenderTarget->getViewPortSize(0))))) {}

void Camera::setActiveRenderingCamera() {
    mGraphicsDevice.getConstantBufferManager().clearBuffer();
    //行列の設定をする
    setMatrix();
    //レンダーターゲットを設定する
    mRenderTarget->activate();
}

void Camera::setActive(bool activeFlag) {
    mIsActive = activeFlag;
    if (activeFlag) {
        setActiveRenderingCamera();
    }
}

void Camera::addPostEffect(std::unique_ptr<PostEffect> effect) {
    mEffects.emplace_back(std::move(effect));
}

void Camera::postEffect() {
    RenderTarget* currentTarget = mRenderTarget.get();
    ConstantBufferManager& m = mGraphicsDevice.getConstantBufferManager();
    ID3D11DeviceContext* context = mGraphicsDevice.getContext().Get();
    Math::Rect uv(0.0f, 0.0f, 1.0f, 1.0f);
    m.setRect(ConstantBufferParameterType::UV, uv);

    //最初に初期化をする
    ID3D11ShaderResourceView* nullSrvs[4] = { nullptr,nullptr,nullptr,nullptr };

    ID3D11RenderTargetView* nullRtvs[2] = { nullptr,nullptr };

    for (auto&& effect : mEffects) {
        context->PSSetShaderResources(0, 4, nullSrvs);
        context->OMSetRenderTargets(2, nullRtvs, nullptr);

        currentTarget->getRenderTargetView(0).getRenderTargetTexture().setData(ShaderInputType::Pixel, 0);
        currentTarget = &effect->set();
        mQuad->render();
    }
    mLastRendered = currentTarget;
}

void Camera::clearPostEffect() {
    mEffects.clear();
}

void Camera::setShaderResource(int slotNum) {
    if (mLastRendered) {
        mLastRendered->getRenderTargetView(0).getRenderTargetTexture().setData(ShaderInputType::Pixel, slotNum);
    }
    else {
        mRenderTarget->getRenderTargetView(0).getRenderTargetTexture().setData(ShaderInputType::Pixel, slotNum);
    }
}

void Camera::clearRenderTarget() {
    mRenderTarget->clear();
}

} //Graphics 
