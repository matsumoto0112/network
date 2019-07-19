#pragma once

#include "Define/Render/LightSettings.h"
#include "Device/Graphics/Buffer/Constant/DirectionalLightCBufferStruct.h"
#include "Device/Graphics/Buffer/Constant/PointLightCBufferStruct.h"

namespace Graphics {

/**
* @struct LightingCBufferStruct
* @brief ライティング用コンスタントバッファ構造体
*/
struct LightingCBufferStruct {
public:
    DirectionalLightCBufferStruct dirLights[Define::LightSettings::DIRECTIONALLIGHT_NUM]; //!< ディレクショナルライト
    PointLightCBufferStruct pLights[Define::LightSettings::POINTLIGHT_NUM]; //!< ポイントライト    
};

} //Graphics 