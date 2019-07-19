#pragma once

#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Camera/Camera.h"
#include "Utility/Math/Matrix4x4.h"

namespace Graphics {

/**
* @class OrthographicCamera
* @brief �����e�J�����N���X
*/
class OrthographicCamera : public Camera {
public:
    /**
    * �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X�Ǘ���
    * @param screenSize �X�N���[���̑傫��
    * @param renderTarget �`��Ώ�
    */
    OrthographicCamera(GraphicsDeviceManager& graphicsDevice,
        const Math::Vector2& screenSize, std::unique_ptr<RenderTarget> renderTarget);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~OrthographicCamera();
    /**
    * @brief �s��̐ݒ�
    */
    virtual void setMatrix() override;
    /**
    * @brief �X�N���[���̑傫���̐ݒ�
    * @param screenSize �ݒ肷��X�N���[���T�C�Y
    */
    void setScreenSize(const Math::Vector2& screenSize);
    /**
    * @brief �X�N���[���̑傫���̎擾
    * @return �J�����ɓo�^���ꂽ�X�N���[���̑傫��
    */
    const Math::Vector2& getScreenSize() const;

    const Math::Vector3& getPosition() const { return mPosition; }
    void setPosition(const Math::Vector3& position) { mPosition = position; }
private:
    /**
    * @brief �����e�s��̐ݒ�
    */
    void setOrthographicMatrix();
private:
    Math::Vector2 mScreenSize; //!< �J�����ɐݒ肳��Ă���X�N���[���̑傫��
    Math::Matrix4x4 mView; //!< �r���[�s��
    Math::Matrix4x4 mProj; //!< �v���W�F�N�V�����s��
    Math::Vector3 mPosition; //!< �J�������W

};

} //Graphics 
