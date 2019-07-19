#pragma once
#include "Define/Resource/PixelShader.h"
#include "Device/Graphics/Shader/PixelShader.h"
#include "Utility/Resource/AbstractResourceStorage.h"

namespace Utility {

class PixelShaderResourceStorage : public AbstractResourceStorage<Define::PixelShaderType, Graphics::PixelShader> {
public:
    PixelShaderResourceStorage();
    ~PixelShaderResourceStorage();
    virtual void importResource(Define::PixelShaderType type, const std::string& filepath) override;
};

} //Utility 