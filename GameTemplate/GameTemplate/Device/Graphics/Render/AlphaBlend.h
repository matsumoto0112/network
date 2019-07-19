#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include "Device/Graphics/Color4.h"

namespace Graphics {

class DirectX11GraphicsDevice;

class AlphaBlend {
public:
    AlphaBlend(DirectX11GraphicsDevice& device);
    ~AlphaBlend();
    void set();
private:
    DirectX11GraphicsDevice& mDevice;
    D3D11_BLEND_DESC mBlendDesc;
    Color4 mBlendFactor;
    Microsoft::WRL::ComPtr<ID3D11BlendState> mBlendState; //!< アルファブレンド
};

} //Graphics 