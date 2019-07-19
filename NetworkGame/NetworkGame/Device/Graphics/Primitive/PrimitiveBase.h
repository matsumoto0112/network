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
* @brief �`��v���~�e�B�u���N���X
*/
class PrimitiveBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    PrimitiveBase(PrimitiveType type,
        GraphicsDeviceManager& graphicsDevice,
        const Transform& transform);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~PrimitiveBase();

    virtual void render();

    Transform* getTransform() { return &mTransform; }

    void setTransform(const Transform& transform) { mTransform = transform; }
private:
    PrimitiveType mType;
    GraphicsDeviceManager& mGraphicsDevice;
    VertexAndIndexBuffer* mBuffer; //!< ���_�E�C���f�b�N�X�o�b�t�@
    Transform mTransform;
};

} //Graphics 

