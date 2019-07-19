#include "DirectionalLight.h"
#include "Device/Graphics/Buffer/Constant/DirectionalLightCBufferStruct.h"

namespace Graphics {

DirectionalLight::DirectionalLight(const DirectionalLightParam& param)
    :Light(param.color,
        [&](DirectionalLightCBufferStruct* buffer) {setBuffer(buffer); }),
    mDirection(param.dir) {}

DirectionalLight::~DirectionalLight() {}

void DirectionalLight::setBuffer(DirectionalLightCBufferStruct* buffer) {
    buffer->color = mColor;
    buffer->direction = mDirection;
}
} //Graphics 
