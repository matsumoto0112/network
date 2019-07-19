#pragma once

#include "Device/Graphics/Color4.h"
#include "Utility/Math/Vector3.h"

namespace Graphics {

/**
* @struct DirectionalLightCBufferStruct
* @brief �f�B���N�V���i�����C�g�̃R���X�^���g�o�b�t�@�p�\����
*/
struct DirectionalLightCBufferStruct {
public:
    Color4 color; //!< �F
    Math::Vector3 direction; //!< ���C�g�̌���
private:
    float dummy; //!< �p�b�L���O�΍�
};


} //Graphics 