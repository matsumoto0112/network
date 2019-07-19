#include "AlphaBlend.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"

namespace Graphics {

AlphaBlend::AlphaBlend(DirectX11GraphicsDevice& device)
    :mDevice(device), mBlendFactor(D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO) {
    //ブレンド描画の設定	   
    ZeroMemory(&mBlendDesc, sizeof(D3D11_BLEND_DESC));
    mBlendDesc.AlphaToCoverageEnable = FALSE;
    mBlendDesc.IndependentBlendEnable = FALSE;
    //全出力先に共通の設定
    for (int i = 0; i < 8; ++i) {
        mBlendDesc.RenderTarget[i].BlendEnable = TRUE;
        mBlendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
        mBlendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_ZERO;
        mBlendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
        mBlendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        mBlendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
        mBlendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        mBlendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }

    HRESULT hr = mDevice.getDevice()->CreateBlendState(&mBlendDesc, &mBlendState);
    mDevice.getContext()->OMSetBlendState(mBlendState.Get(), mBlendFactor.get().data(), 0xffffffff);
}

AlphaBlend::~AlphaBlend() {}

void AlphaBlend::set() {
    mDevice.getContext()->OMSetBlendState(mBlendState.Get(), mBlendFactor.get().data(), 0xffffffff);
}

} //Graphics 
