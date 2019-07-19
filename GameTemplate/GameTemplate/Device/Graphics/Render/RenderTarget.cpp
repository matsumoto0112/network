#include "RenderTarget.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"
#include "Device/Graphics/Render/Viewport.h"
#include "Device/Graphics/Render/RenderTargetView.h"
#include "Device/Graphics/Render/DepthStencilView.h"
#include "Utility/Debug.h"

namespace Graphics {

RenderTarget::RenderTarget(DirectX11GraphicsDevice& graphicsDevice,
    const Viewport& viewport,
    std::unique_ptr<RenderTargetView> renderTargetView,
    std::unique_ptr<DepthStencilView> depthStencil,
    const Color4& clearColor)
    :mGraphicsDevice(graphicsDevice), mDepthStencil(std::move(depthStencil)), mClearColor(clearColor) {
    mViewPorts.emplace_back(viewport);
    mRenderTargetView.emplace_back(std::move(renderTargetView));
}

RenderTarget::~RenderTarget() {
    mRenderTargetView.clear();
    mViewPorts.clear();
}

void RenderTarget::addViewPort(const Viewport& viewport) {
    mViewPorts.emplace_back(viewport);
}

void RenderTarget::addRenderTarget(std::unique_ptr<RenderTargetView> renderTargetView) {
    mRenderTargetView.emplace_back(std::move(renderTargetView));
}

RenderTargetView& RenderTarget::getRenderTargetView(int id) {
    MY_ASSERTION(id < (int)mRenderTargetView.size(),
        "インデックスが配列の範囲外です。");
    return *mRenderTargetView[id];
}

void RenderTarget::activate() {
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = mGraphicsDevice.getContext();
    std::vector<ID3D11RenderTargetView*> view(mRenderTargetView.size());
    for (int i = 0; i < (int)view.size(); i++) {
        view[i] = mRenderTargetView[i]->getRenderTargetView().Get();
    }
    if (mDepthStencil) {
        context->OMSetRenderTargets(view.size(),
            view.data(), mDepthStencil->getView().Get());
        mDepthStencil->clear();
    }
    else {
        context->OMSetRenderTargets(view.size(),
            view.data(), nullptr);
    }
    for (int i = 0; i < (int)mRenderTargetView.size(); i++) {
        //context->ClearRenderTargetView(mRenderTargetView[i]->getRenderTargetView().Get(), mClearColor.get().data());
    }
    context->RSSetViewports(mViewPorts.size(), mViewPorts.front());
}

Math::Vector2 RenderTarget::getViewPortSize(int id) {
    MY_ASSERTION(id < (int)mViewPorts.size(),
        "添え字が配列の範囲外です");
    return mViewPorts[id].getSize();
}

void RenderTarget::clear() {
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = mGraphicsDevice.getContext();
    for (auto&& rtv : mRenderTargetView) {
        rtv->clear(mClearColor);
    }
}

} //Graphics 
