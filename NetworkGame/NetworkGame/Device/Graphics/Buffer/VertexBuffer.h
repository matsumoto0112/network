#pragma once

#include <vector>
#include <wrl/client.h>
#include <d3d11.h>

#include "Utility/Debug.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"
#include "Device/Graphics/Buffer/VertexBufferBindData.h"

namespace Graphics {

class GraphicsDeviceManager;

/**
* @class VertexBuffer
* @brief 頂点バッファ管理
*/
class VertexBuffer {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @tparam vertices 頂点データ
    */
    template<class T>
    VertexBuffer(GraphicsDeviceManager& graphicsDevice, const std::vector<T>& vertices);
    /**
    * @brief デストラクタ
    */
    ~VertexBuffer();
    /**
    * @brief 頂点データのセット
    */
    void setData();
private:
    /**
    * @brief 頂点バッファの作成
    * @tparam vertices 頂点データ
    */
    template<class T>
    void createBuffer(const std::vector<T>& vertices);
private:
    DirectX11GraphicsDevice& mDevice; //!< DirectX11用グラフィックデバイス
    std::unique_ptr<VertexBufferBindData> mData; //!< デバイス転送用データ
};

//コンストラクタ
template<class T>
inline VertexBuffer::VertexBuffer(GraphicsDeviceManager& graphicsDevice, const std::vector<T>& vertices)
    :mDevice(graphicsDevice.getDirectX11Device()),
    mData(std::make_unique<VertexBufferBindData>()) {
    createBuffer(vertices);
}


//頂点バッファの作成
template<class T>
inline void VertexBuffer::createBuffer(const std::vector<T>& vertices) {
    //頂点のサイズを保存
    mData->mStride = sizeof(T);
    //オフセットは基本使用しない
    mData->mOffset = 0;

    //バッファデータの作成
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.ByteWidth = mData->mStride * vertices.size();
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    //サブリソースの作成
    D3D11_SUBRESOURCE_DATA subResource;
    ZeroMemory(&subResource, sizeof(subResource));
    subResource.SysMemPitch = 0;
    subResource.SysMemSlicePitch = 0;
    subResource.pSysMem = vertices.data();
    HRESULT hr = mDevice.getDevice()->CreateBuffer(&desc, &subResource, &mData->mBuffer);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "頂点バッファ作成失敗");
    }
}

} //Graphics 