#pragma once

#include <memory>
#include <vector>
#include "Utility/Transform.h"
#include "Device/Graphics/Shader/PostEffect.h"

namespace Graphics {

class GraphicsDeviceManager;
class RenderTarget;
class Quad2D;

/**
* @class Camera
* @brief �J�������ۃN���X
*/
class Camera {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Camera(GraphicsDeviceManager& graphicsDevice, std::unique_ptr<RenderTarget> renderTarget);
    /**
    * @brief ���z�f�X�g���N�^
    */
    virtual ~Camera() = default;
    /**
    * @brief �s��̓]��
    */
    virtual void setMatrix() = 0;
    /**
    * @brief ���̃J�����ɕ`��Ώۂ�ύX����
    * @details �����ɕ����̃J�������A�N�e�B�u�ɂ��邱�Ƃ͂ł��Ȃ��B��ɍŐV�̈���A�N�e�B�u�ɂȂ�
    */
    void setActiveRenderingCamera();
    /**
    * @brief �A�N�e�B�u��Ԃ̕ύX
    * @param activeFlag �ݒ肷����
    */
    void setActive(bool activeFlag);

    /**
    * @brief �A�N�e�B�u��Ԃ̎擾
    */
    bool isActive() const { return mIsActive; }
    /**
    * @brief �|�X�g�G�t�F�N�g�̒ǉ�
    * @param effect �ǉ�����G�t�F�N�g
    */
    void addPostEffect(std::unique_ptr<PostEffect> effect);
    /**
    * @brief �|�X�g�G�t�F�N�g�J�n
    */
    void postEffect();
    /**
    * @brief �|�X�g�G�t�F�N�g���X�g�̃N���A
    */
    void clearPostEffect();

    /**
    * @brief �J�����̕`�挋�ʂ��V�F�[�_�[�ɓ]������
    * @param slotNum �]�������̃e�N�X�`���ԍ�
    */
    void setShaderResource(int slotNum);

    void clearRenderTarget();
protected:
    GraphicsDeviceManager& mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    std::unique_ptr<RenderTarget> mRenderTarget; //!< �`��o�͐�
    bool mIsActive; //!< �A�N�e�B�u���
    std::vector<std::unique_ptr<PostEffect>> mEffects; //!< �|�X�g�G�t�F�N�g���X�g
    RenderTarget* mLastRendered; //!< �Ō�ɕ`�悵���^�[�Q�b�g
    std::unique_ptr<Quad2D> mQuad; //!< �`��Ɏg�p�����`
};

} //Graphics 