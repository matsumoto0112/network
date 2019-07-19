#pragma once
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Quaternion.h"

namespace Math {
class Matrix4x4;
} //Math 

/**
* @class Transform
* @brief 3D�g�����X�t�H�[���N���X
*/
class Transform {
public:
    /**
    * @brief �f�t�H���g�R���X�g���N�^
    */
    Transform();
    /**
    * @brief �R���X�g���N�^
    * @param position ���W
    * @param rotate ��]
    * @param scale �傫��
    */
    Transform(const Math::Vector3& position,
        const Math::Quaternion& rotate,
        const Math::Vector3& scale);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Transform();
    /**
    * @brief ���W�̎擾
    */
    const Math::Vector3& getPosition() const { return mPosition; }
    /**
    * @brief ��]�̎擾
    */
    const Math::Quaternion& getRotate() const { return mRotation; }
    /**
    * @brief �傫���̎擾
    */
    const Math::Vector3& getScale() const { return mScale; }
    /**
    * @brief ���W�̐ݒ�
    */
    void setPosition(const Math::Vector3& position) { mPosition = position; }
    /**
    * @brief ��]�̐ݒ�
    */
    void setRotate(const Math::Quaternion& rotate) { mRotation = rotate; }
    /**
    * @brief �傫���̐ݒ�
    */
    void setScale(const Math::Vector3& scale) { mScale = scale; }
    /**
    * @brief SRT�s��̍쐬
    */
    Math::Matrix4x4 createSRTMatrix() const;
    /**
    * @brief ���[�J����SRT�s��̍쐬
    */
    Math::Matrix4x4 createLocalSRTMatrix() const;
    void setParent(Transform* parent);

private:
    Transform* mParent; //!< �e�̃g�����X�t�H�[��
    Math::Vector3 mPosition; //!< ���W
    Math::Quaternion mRotation; //!< ��]
    Math::Vector3 mScale; //!< �傫��
};