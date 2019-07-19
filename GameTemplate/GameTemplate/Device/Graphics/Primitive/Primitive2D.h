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
* 2D�v���~�e�B�u���N���X
*/
class Primitive2D {
public:
    /**
    * �R���X�g���N�^
    * @param type �v���~�e�B�u�̌`��
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param transform �v���~�e�B�u�̃g�����X�t�H�[��
    */
    Primitive2D(PrimitiveType type,
        GraphicsDeviceManager& graphicsDevice,
        const Transform2D& transform);
    /**
    * �f�X�g���N�^
    */
    virtual ~Primitive2D();
    /**
    * �`�悷��
    */
    virtual void render();
    /**
    * �g�����X�t�H�[���̎擾
    */
    Transform2D& getTransform() { return mTransform; }
    /**
    * �g�����X�t�H�[���̐ݒ�
    */
    void setTransform(const Transform2D& transform) { mTransform = transform; }
protected:
    PrimitiveType mType; //!< �`��
    GraphicsDeviceManager& mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    VertexAndIndexBuffer* mBuffer; //!< ���_�E�C���f�b�N�X�o�b�t�@
    Transform2D mTransform; //!< �v���~�e�B�u�̃g�����X�t�H�[��
};

} //Graphics 
