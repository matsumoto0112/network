#include "Effect.h"
#include "Device/Graphics/Shader/VertexShader.h"
#include "Device/Graphics/Shader/PixelShader.h"

namespace Graphics {

Effect::Effect(std::shared_ptr<VertexShader> vertexShader,
    std::shared_ptr<PixelShader> pixelShader)
    :mVertexShader(vertexShader), mPixelShader(pixelShader) {}

Effect::~Effect() {}

void Effect::set() {
    mVertexShader->set();
    mPixelShader->set();
}

} //Graphics 
