#include "PointLight.h"
#include "Device/Graphics/Buffer/Constant/LightingCBufferStruct.h"

Graphics::PointLight::PointLight(const PointLightParam& param)
    :Light(param.color,
        [this](PointLightCBufferStruct* buffer) {setBuffer(buffer); }), mPosition(param.pos), mAttenuation(param.attenuation) {}

Graphics::PointLight::~PointLight() {}

void Graphics::PointLight::setBuffer(PointLightCBufferStruct* buffer) {
    buffer->light = mPosition;
    buffer->color = mColor;
    memcpy_s(buffer->attenuation, sizeof(buffer->attenuation),
        mAttenuation.attenuation.data(), sizeof(float) * 4);
}
