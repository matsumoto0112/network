#pragma once

#include <memory>

namespace Graphics {
class GraphicsDeviceManager;
class Sprite2D;
class VertexAndIndexBuffer;
class VertexShader;
class PixelShader;
class Sampler;

/**
* @class SpriteRenderer
* @brief スプライト描画器
*/
class SpriteRenderer {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    */
    SpriteRenderer(GraphicsDeviceManager& graphicsDevice);
    /**
    * @brief デストラクタ
    */
    ~SpriteRenderer();
    /**
    * @brief スプライトを描画する
    * @param sprite 描画するスプライト
    */
    void draw(Sprite2D* sprite);
private:
    GraphicsDeviceManager& mGraphicsDevice; //!< グラフィックデバイス
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer; //!< 頂点・インデックスバッファ
    std::unique_ptr<VertexShader> mVertexShader; //!< 頂点シェーダー
    std::unique_ptr<PixelShader> mPixelShader; //!< ピクセルシェーダー
    std::unique_ptr<Sampler> mSampler; //!< サンプラー
};

} //Graphics 
