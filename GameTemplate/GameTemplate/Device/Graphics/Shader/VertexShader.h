#pragma once

#include <vector>
#include <memory>
#include <d3d11.h>
#include "Device/Graphics/Shader/ShaderBase.h"
#include "Device/Graphics/Shader/VertexShaderData.h"

namespace Graphics {
class GraphicsDeviceManager;

/**
* @class VertexShader
* @brief ���_�V�F�[�_
*/
class VertexShader : public ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param filename �V�F�[�_�t�@�C����
    */
    VertexShader(GraphicsDeviceManager& graphicsDevice, const std::string& name);
    /**
    * @brief �f�X�g���N�^
    */
    ~VertexShader();
    /**
    * @brief ���_�V�F�[�_�̃Z�b�g
    */
    void set() override;
private:
    /**
    * @brief ���_�V�F�[�_�̍쐬
    * @param filename �V�F�[�_�t�@�C����
    */
    void create(const std::string& name);
private:
    std::unique_ptr<VertexShaderData> mShaderData; //!< �V�F�[�_�[�̃f�[�^
};
} //Graphics 
