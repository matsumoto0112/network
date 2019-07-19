#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include "Utility/Math/Vector2.h"

namespace Graphics {

class DirectX11GraphicsDevice;

class TextureBuffer {
    using TexPtr = Microsoft::WRL::ComPtr<ID3D11Texture2D>;
public:
    TextureBuffer(DirectX11GraphicsDevice& graphicsDevice);
    TextureBuffer(DirectX11GraphicsDevice& graphicsDevice, const D3D11_TEXTURE2D_DESC& desc);
    TextureBuffer(DirectX11GraphicsDevice& graphicsDevice,
        const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA& sub);
    ~TextureBuffer();
    TexPtr getBuffer() const { return mTextureBuffer; }
    const Math::Vector2& getSize() const { return mSize; }
private:
    TexPtr mTextureBuffer;
    Math::Vector2 mSize;
};

} //Graphics 