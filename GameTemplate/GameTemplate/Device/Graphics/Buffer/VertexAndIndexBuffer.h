#pragma once

#include <memory>
#include <vector>
#include <d3d11.h>
#include "Device/Graphics/Vertex/Vertex.h"
#include "Device/Graphics/Buffer/VertexBuffer.h"
#include "Device/Graphics/Buffer/IndexBuffer.h"

namespace Graphics {

class GraphicsDeviceManager;

/**
* @class VertexAndIndexBuffer
* @brief 頂点・インデックスバッファをまとめたクラス
*/
class VertexAndIndexBuffer {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @tparam vertices 頂点データ
    * @param indices インデックスデータ
    * @param topology プリミティブトポロジーの種類
    */
    template<class T>
    VertexAndIndexBuffer(GraphicsDeviceManager& graphicsDevice,
        const std::vector<T>& vertices,
        const std::vector<WORD>& indices,
        PrimitiveTopology topology);
    /**
    * @brief デストラクタ
    */
    ~VertexAndIndexBuffer();

    /**
    * @brief 描画する
    * @details 描画前に描画に必要なデータを送っておく必要がある
    */
    void render();
private:
    GraphicsDeviceManager& mGraphicsDevice; //!< グラフィックデバイス
    std::unique_ptr<VertexBuffer> mVertexBuffer; //!< 頂点バッファ
    std::unique_ptr<IndexBuffer> mIndexBuffer; //!< インデックスバッファ
};

template<class T>
inline VertexAndIndexBuffer::VertexAndIndexBuffer(GraphicsDeviceManager& graphicsDevice,
    const std::vector<T>& vertices,
    const std::vector<WORD>& indices,
    PrimitiveTopology topology)
    :mGraphicsDevice(graphicsDevice),
    mVertexBuffer(std::make_unique<VertexBuffer>(graphicsDevice, vertices)),
    mIndexBuffer(std::make_unique<IndexBuffer>(graphicsDevice, indices, topology)) {}
} //Graphics 