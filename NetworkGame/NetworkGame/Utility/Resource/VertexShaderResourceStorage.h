#pragma once
#include <unordered_map>
#include "Define/Resource/VertexShader.h"
#include "Device/Graphics/Shader/VertexShader.h"
#include "Utility/Resource/AbstractResourceStorage.h"

namespace Utility {

class VertexShaderResourceStorage : public AbstractResourceStorage<Define::VertexShaderType, Graphics::VertexShader> {
public:
    VertexShaderResourceStorage();
    ~VertexShaderResourceStorage();
    virtual void importResource(Define::VertexShaderType, const std::string& filepath) override;
};

} //Utility 