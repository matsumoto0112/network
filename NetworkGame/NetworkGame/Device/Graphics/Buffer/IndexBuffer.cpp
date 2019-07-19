#include "IndexBuffer.h"
#include "Utility/Debug.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"

namespace {
//PrimitiveTopologyからD3D11_PRIMITIVE_TOPOLOGYに変換する
D3D11_PRIMITIVE_TOPOLOGY convert(Graphics::PrimitiveTopology type) {
    D3D11_PRIMITIVE_TOPOLOGY result;
    switch (type) {
    case Graphics::PrimitiveTopology::LineList:
        result = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
        break;
    case Graphics::PrimitiveTopology::TriangleList:
        result = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    case Graphics::PrimitiveTopology::TriangleStrip:
        result = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        break;
    default:
        MY_ASSERTION(false, "未定義のプリミティブトポロジーの種類が選択されました。");
        break;
    }
    return result;
}
}

namespace Graphics {

IndexBuffer::IndexBuffer(GraphicsDeviceManager& graphicsDevice,
    const std::vector<WORD>& indices, PrimitiveTopology topology)
    :mGraphicsDevice(graphicsDevice.getDirectX11Device()) {
    setBuffer(indices, topology);
}

IndexBuffer::~IndexBuffer() {}

void IndexBuffer::setBuffer(const std::vector<WORD>& indices, PrimitiveTopology topology) {
    mIndexCount = indices.size();

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.ByteWidth = sizeof(WORD) * mIndexCount;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subResource;
    ZeroMemory(&subResource, sizeof(subResource));
    subResource.pSysMem = indices.data();
    subResource.SysMemPitch = 0;
    subResource.SysMemSlicePitch = 0;

    mData = std::make_unique<IndexBufferBindData>();
    HRESULT hr = mGraphicsDevice.getDevice()->CreateBuffer(&desc, &subResource, &mData->mBuffer);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "バッファの作成に失敗しました。");
        return;
    }
    mData->mTopology = convert(topology);
}

void IndexBuffer::setData() {
    mGraphicsDevice.getContext()->IASetIndexBuffer(mData->mBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    mGraphicsDevice.getContext()->IASetPrimitiveTopology(mData->mTopology);
}

void IndexBuffer::drawCall() {
    mGraphicsDevice.getContext()->DrawIndexed(mIndexCount, 0, 0);
}

} //Graphics 
