#include "DepthStencilView.h"
#include "Utility/Debug.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"

namespace Graphics {

DepthStencilView::DepthStencilView(
    DirectX11GraphicsDevice& device, UINT backBufferWidth, UINT backBufferHeight,
    UINT count, UINT quality)
    :mDevice(device) {
    //深度・ステンシルバッファ作成
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.Width = backBufferWidth;
    depthStencilDesc.Height = backBufferHeight;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = count;
    depthStencilDesc.SampleDesc.Quality = quality;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;
    HRESULT hr = device.getDevice()->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthStencil);
    if (FAILED(hr)) {
        MY_ASSERTION(SUCCEEDED(hr), "DepthStencil用のテクスチャ作成失敗");
        return;
    }
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = depthStencilDesc.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = device.getDevice()->CreateDepthStencilView(mDepthStencil.Get(), &descDSV, &mDepthStencilView);
    if (FAILED(hr)) {
        MY_ASSERTION(SUCCEEDED(hr), "DepthStencilView作成失敗");
        return;
    }
}

DepthStencilView::~DepthStencilView() {}

Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView::getView() const {
    return mDepthStencilView;
}

void DepthStencilView::clear() {
    mDevice.getContext()->ClearDepthStencilView(mDepthStencilView.Get(),
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

} //Graphics 
