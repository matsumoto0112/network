#pragma once

#include "Device/Graphics/Camera/Camera.h"
#include "Utility/Math/Vector2.h"
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Matrix4x4.h"
#include "Utility/Transform.h"

#undef near
#undef far

namespace Graphics {

/**
* @class PerspectiveCameraInfo
* @brief �J�����̏��
*/
struct PerspectiveCameraInfo {
    Math::Vector3 eye; //!< �J�������W
    Math::Vector3 at; //!< �����_
    Math::Vector3 up; //!< ���_�̏����
    float fov; //!< ����p�i�x�j
    Math::Vector2 screenSize; //!< �X�N���[���̑傫��
    float near; //!< �ŋߓ_
    float far; //!< �ŉ��_
};

/**
* @class PerspectiveCamera
* @brief �������e�J�����N���X
*/
class PerspectiveCamera : public Camera {
private:
    using Vec2 = Math::Vector2;
    using Vec3 = Math::Vector3;
    using Mat4 = Math::Matrix4x4;
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param info �J�����̏��
    * @param renderTarget �`��Ώ�
    */
    PerspectiveCamera(GraphicsDeviceManager& graphicsDevice, const PerspectiveCameraInfo& info,
        std::unique_ptr<RenderTarget> renderTarget);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~PerspectiveCamera();
    /**
    * @brief �r���[�s��̎擾
    */
    const Mat4& getView() const;
    /**
    * @brief �v���W�F�N�V�����s��̎擾
    */
    const Mat4& getProjection() const;
    /**
    * @brief �J�������W�̐ݒ�
    * @param position �ݒ肷����W
    * @param keepLookAt ���_�����W�ɍ��킹�đ��ΓI�Ɉړ������邩
    */
    void setPosition(const Vec3& position, bool keepLookAt = false);
    /**
    * @brief �J�������W�̎擾
    */
    const Vec3& getPosition() const;
    /**
    * @brief �J�����̒����_�̐ݒ�
    */
    void setLookAt(const Vec3& at);
    /**
    * @brief �J�����̒����_�̎擾
    */
    const Vec3& getLookAt() const;
    /**
    * @brief �J�����̏�����̐ݒ�
    */
    void setUpVector(const Vec3& up);
    /**
    * @brief �J�����̏�����̎擾
    */
    const Vec3& getUpVector() const;

    /**
    * @brief �J�������̍Đݒ�
    * @param eye �J�������W
    * @param at �����_
    * @param up ���_�̏����
    */
    void setCameraView(const Vec3& eye, const Vec3& at, const Vec3& up);
    /**
    * @brief �v���W�F�N�V�����s��̍Đݒ�
    * @param fov ����p�i�x�j
    * @param screen �X�N���[���̑傫��
    * @param near �ŋߓ_
    * @param far �ŉ��_
    */
    void setProjection(float fov, const Vec2& screen, float near, float far);
    /**
    * @brief �s����R���X�^���g�o�b�t�@�ɓ]������
    */
    virtual void setMatrix() override;
protected:
    Vec3 mCameraPosition; //!< �J�������W
    Vec3 mCameraLookAt; //!< �J���������_
    Vec3 mCameraUpVector; //!< �J���������
    Mat4 mView; //!< �r���[�s��
    Mat4 mProjection; //!< �v���W�F�N�V�����s��
    float mLength; //!< �J�����̍��W���王�_�܂ł̋���
};

} //Graphics 