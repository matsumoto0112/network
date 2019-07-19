#include "Sampler.h"
#include <assert.h>
#include "Device/Graphics/DirectX11GraphicsDevice.h"
#include "Device/Graphics/Shader/ShaderInputType.h"
#include "Utility/Debug.h"

namespace {

D3D11_TEXTURE_ADDRESS_MODE convert(Graphics::TextureAddressMode addressMode) {
    switch (addressMode) {
    case Graphics::TextureAddressMode::Wrap:
        return D3D11_TEXTURE_ADDRESS_WRAP;
    case Graphics::TextureAddressMode::Clamp:
        return D3D11_TEXTURE_ADDRESS_CLAMP;
    default:
        //_ASSERT_EXPR(0, Utility::debugMessage("不正なテクスチャモードが選択されました。"));
        return (D3D11_TEXTURE_ADDRESS_MODE)0;
    }
}

D3D11_FILTER convert(Graphics::TextureFilterMode filterMode) {
    switch (filterMode) {
    case Graphics::TextureFilterMode::MinMagMipLinear:
        return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    case Graphics::TextureFilterMode::MinMagMipPoint:
        return D3D11_FILTER_MIN_MAG_MIP_POINT;
    default:
        //_ASSERT_EXPR(0, Utility::debugMessage("不正なフィルタリングモードが選択されました。"));
        return (D3D11_FILTER)0;
    }
}
}

namespace Graphics {

Sampler::Sampler(DirectX11GraphicsDevice& graphicsDevice, TextureAddressMode addressMode, TextureFilterMode filterMode)
    :mGraphicsDevice(graphicsDevice) {
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = convert(filterMode);
    D3D11_TEXTURE_ADDRESS_MODE texAddressMode = convert(addressMode);
    sampDesc.AddressU = texAddressMode;
    sampDesc.AddressV = texAddressMode;
    sampDesc.AddressW = texAddressMode;
    sampDesc.MaxAnisotropy = 1;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = -3.402823466e+38F;
    sampDesc.MaxLOD = 3.402823466e+38F;
    HRESULT hr = mGraphicsDevice.getDevice()->CreateSamplerState(&sampDesc, &mSamplerState);
    //_ASSERT_EXPR(SUCCEEDED(hr),
    //    Utility::debugMessage("サンプラー作成失敗"));
}

Sampler::Sampler(DirectX11GraphicsDevice& graphicsDevice, const SamplerState& sampler)
    :mGraphicsDevice(graphicsDevice), mSamplerState(sampler) {}

Sampler::~Sampler() {}

void Sampler::setData(ShaderInputType inputType, UINT slotNumber) {
    switch (inputType) {
    case Graphics::ShaderInputType::Vertex:
        mGraphicsDevice.getContext()->VSSetSamplers(slotNumber, 1, mSamplerState.GetAddressOf());
        break;
    case Graphics::ShaderInputType::Pixel:
        mGraphicsDevice.getContext()->PSSetSamplers(slotNumber, 1, mSamplerState.GetAddressOf());
        break;
    }
}

} //Graphics 
