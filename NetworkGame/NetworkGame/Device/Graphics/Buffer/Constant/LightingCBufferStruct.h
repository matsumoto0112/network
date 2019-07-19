#pragma once

#include "Define/Render/LightSettings.h"
#include "Device/Graphics/Buffer/Constant/DirectionalLightCBufferStruct.h"
#include "Device/Graphics/Buffer/Constant/PointLightCBufferStruct.h"

namespace Graphics {

/**
* @struct LightingCBufferStruct
* @brief ���C�e�B���O�p�R���X�^���g�o�b�t�@�\����
*/
struct LightingCBufferStruct {
public:
    DirectionalLightCBufferStruct dirLights[Define::LightSettings::DIRECTIONALLIGHT_NUM]; //!< �f�B���N�V���i�����C�g
    PointLightCBufferStruct pLights[Define::LightSettings::POINTLIGHT_NUM]; //!< �|�C���g���C�g    
};

} //Graphics 