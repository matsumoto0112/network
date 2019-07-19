#pragma once

#include <memory>
#include <vector>
#include "Utility/Math/Matrix4x4.h"
#include "Utility/Transform2D.h"

namespace Graphics {

enum class PrimitiveType;
class GraphicsDeviceManager;
class VertexAndIndexBuffer;

/**
* @class Primitive2D
* 2Dプリミティブ基底クラス
*/
class Primitive2D {
public:
    /**
    * コンストラクタ
    * @param type プリミティブの形状
    * @param graphicsDevice グラフィックデバイス
    * @param transform プリミティブのトランスフォーム
    */
    Primitive2D(PrimitiveType type,
        GraphicsDeviceManager& graphicsDevice,
        const Transform2D& transform);
    /**
    * デストラクタ
    */
    virtual ~Primitive2D();
    /**
    * 描画する
    */
    virtual void render();
    /**
    * トランスフォームの取得
    */
    Transform2D& getTransform() { return mTransform; }
    /**
    * トランスフォームの設定
    */
    void setTransform(const Transform2D& transform) { mTransform = transform; }
protected:
    PrimitiveType mType; //!< 形状
    GraphicsDeviceManager& mGraphicsDevice; //!< グラフィックデバイス
    VertexAndIndexBuffer* mBuffer; //!< 頂点・インデックスバッファ
    Transform2D mTransform; //!< プリミティブのトランスフォーム
};

} //Graphics 
