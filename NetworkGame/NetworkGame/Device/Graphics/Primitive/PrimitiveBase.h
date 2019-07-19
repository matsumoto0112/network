#pragma once
#include <memory>
#include <vector>
#include "Utility/Math/Matrix4x4.h"
#include "Utility/Transform.h"
#include "Device/Graphics/Primitive/PrimitiveType.h"

namespace Graphics {

class GraphicsDeviceManager;
class VertexAndIndexBuffer;

/**
* @class PrimitiveBase
* @brief 描画プリミティブ基底クラス
*/
class PrimitiveBase {
public:
    /**
    * @brief コンストラクタ
    */
    PrimitiveBase(PrimitiveType type,
        GraphicsDeviceManager& graphicsDevice,
        const Transform& transform);
    /**
    * @brief デストラクタ
    */
    virtual ~PrimitiveBase();

    virtual void render();

    Transform* getTransform() { return &mTransform; }

    void setTransform(const Transform& transform) { mTransform = transform; }
private:
    PrimitiveType mType;
    GraphicsDeviceManager& mGraphicsDevice;
    VertexAndIndexBuffer* mBuffer; //!< 頂点・インデックスバッファ
    Transform mTransform;
};

} //Graphics 

