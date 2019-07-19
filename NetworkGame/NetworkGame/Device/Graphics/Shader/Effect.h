#pragma once

#include <memory>
#include "Device/Graphics/Shader/VertexShader.h"
#include "Device/Graphics/Shader/PixelShader.h"

namespace Graphics {

class Effect {
public:
    Effect(std::shared_ptr<VertexShader> vertexShader,
        std::shared_ptr<PixelShader> pixelShader);
    ~Effect();
    void set();
private:
    std::shared_ptr<VertexShader> mVertexShader;
    std::shared_ptr<PixelShader> mPixelShader;
};

} //Graphics 