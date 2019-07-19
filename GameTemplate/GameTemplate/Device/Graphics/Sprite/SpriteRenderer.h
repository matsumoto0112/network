#pragma once

#include <memory>

namespace Graphics {
class GraphicsDeviceManager;
class Sprite2D;
class VertexAndIndexBuffer;
class VertexShader;
class PixelShader;
class Sampler;

/**
* @class SpriteRenderer
* @brief �X�v���C�g�`���
*/
class SpriteRenderer {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    */
    SpriteRenderer(GraphicsDeviceManager& graphicsDevice);
    /**
    * @brief �f�X�g���N�^
    */
    ~SpriteRenderer();
    /**
    * @brief �X�v���C�g��`�悷��
    * @param sprite �`�悷��X�v���C�g
    */
    void draw(Sprite2D* sprite);
private:
    GraphicsDeviceManager& mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer; //!< ���_�E�C���f�b�N�X�o�b�t�@
    std::unique_ptr<VertexShader> mVertexShader; //!< ���_�V�F�[�_�[
    std::unique_ptr<PixelShader> mPixelShader; //!< �s�N�Z���V�F�[�_�[
    std::unique_ptr<Sampler> mSampler; //!< �T���v���[
};

} //Graphics 
