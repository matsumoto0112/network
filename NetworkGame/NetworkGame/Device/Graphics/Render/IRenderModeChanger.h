#pragma once

#include "Device/Graphics/Render/RasterizerMode.h"

namespace Graphics {

/**
* @class IRenderModeChanger
* @brief �`�惂�[�h�ύX�C���^�[�t�F�[�X
*/
class IRenderModeChanger
{
public:
    /**
    * @brief ���z�f�X�g���N�^
    */
    virtual ~IRenderModeChanger() = default;
    /**
    * @brief �`�惂�[�h�̐ݒ�
    * @param cull �J�����O�̐ݒ�
    * @param fill �h��Ԃ��̐ݒ�
    */
    virtual void setRenderMode(CullMode cull, FillMode fill) = 0;
    /**
    * @brief ���݂̃J�����O���[�h�̎擾
    */
    virtual CullMode getCullMode() const = 0;
    /**
    * @brief �h��Ԃ����[�h�̎擾
    */
    virtual FillMode getFillMode() const = 0;
};

} //Graphics 
