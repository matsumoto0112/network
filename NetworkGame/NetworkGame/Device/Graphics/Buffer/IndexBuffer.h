#pragma once

#include <vector>
#include <d3d11.h>
#include <memory>
#include <wrl/client.h>
#include "Device/Graphics/Buffer/IndexBufferBindData.h"

namespace Graphics {

//前方宣言
class GraphicsDeviceManager;
class DirectX11GraphicsDevice;

/**
* @class IndexBuffer
* @brief インデックスバッファ管理クラス
*/
class IndexBuffer {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @param indices インデックスデータ
    * @param topology プリミティブトポロジーの種類
    */
    IndexBuffer(GraphicsDeviceManager& graphicsDevice,
        const std::vector<WORD>& indices, PrimitiveTopology topology);
    /**
    * @brief デストラクタ
    */
    ~IndexBuffer();
    /**
    * @brief インデックスデータのセット
    */
    void setData();
    /**
    * @brief 描画指令を送る
    */
    void drawCall();
private:
    /**
    * @brief インデックスデータの設定
    * @param indices インデックスデータ
    */
    void setBuffer(const std::vector<WORD>& indices, PrimitiveTopology topology);
private:
    DirectX11GraphicsDevice& mGraphicsDevice; //!< DirectX11用グラフィックデバイス
    std::unique_ptr<IndexBufferBindData> mData; //!< インデックスバッファのデータ
    UINT mIndexCount; //!< 頂点数
};

} //Graphics 