#pragma once

#include <string>
#include "Device/Graphics/Shader/ShaderBase.h"
#include "Device/Graphics/Shader/PixelShaderData.h"

namespace Graphics {
class GraphicsDeviceManager;

/**
* @class PixelShader
* @brief �s�N�Z���V�F�[�_
*/
class PixelShader : public ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param filename �V�F�[�_�t�@�C����
    */
    PixelShader(GraphicsDeviceManager& graphicsDevice, const std::string& filename);
    /**
    * @brief �f�X�g���N�^
    */
    ~PixelShader();
    /**
    * @brief �s�N�Z���V�F�[�_�̃Z�b�g
    */
    void set();
private:
    /**
    * @brief �s�N�Z���V�F�[�_�̍쐬
    * @param name �V�F�[�_�t�@�C����
    */
    void create(const std::string& name);
private:
    std::unique_ptr<PixelShaderData> mShaderData; //!< �V�F�[�_�[�̃f�[�^
};

} //Graphics 
