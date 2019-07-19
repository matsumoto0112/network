#pragma once
#include "Device/Graphics/Camera/PerspectiveCamera.h"

namespace Graphics {

/**
* @class FPSCamera
* @brief FPS�p�J����
*/
class FPSCamera :public PerspectiveCamera {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param info �p�[�X�y�N�e�B�u�J���������ݒ�
    * @param renderTarget �`��o�͐�
    */
    FPSCamera(GraphicsDeviceManager& graphicsDevice,
        const PerspectiveCameraInfo& info,
        std::unique_ptr<RenderTarget> renderTarget);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~FPSCamera();
    /**
    * @brief �ړ��ʂƉ�]����J�����̍��W�ƌ������v�Z����
    * @param movement �ړ���
    * @param x ���������̉�]��(deg)
    * @param y ���������̉�]��(deg)
    */
    void calculatePositionAndRotation(const Math::Vector3& movement, float x, float y);
private:
};

} //Graphics 