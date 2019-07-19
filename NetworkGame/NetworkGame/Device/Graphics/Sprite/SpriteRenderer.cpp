#include "SpriteRenderer.h"
#include <vector>
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Texture/Texture.h"
#include "Device/Graphics/Sprite/Sprite2D.h"
#include "Device/Graphics/Shader/ShaderInputType.h"
#include "Device/Graphics/Vertex/Vertex.h"
#include "Device/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Device/Graphics/Shader/VertexShader.h"
#include "Device/Graphics/Shader/PixelShader.h"
#include "Device/Graphics/Texture/Sampler.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/Render/IRenderModeChanger.h"

namespace Graphics {

SpriteRenderer::SpriteRenderer(GraphicsDeviceManager& graphicsDevice)
    :mGraphicsDevice(graphicsDevice) {
    std::vector<TextureVertex> vertices
    {
        { 0.0f,0.0f,0.0f,1.0f,0.0f,0.0f },
        { 1.0f,0.0f,0.0f,1.0f,1.0f,0.0f },
        { 1.0f,1.0f,0.0f,1.0f,1.0f,1.0f },
        { 0.0f,1.0f,0.0f,1.0f,0.0f,1.0f },
    };
    std::vector<WORD> indices = { 0,1,2,0,2,3 };
    mVIBuffer = std::make_unique<VertexAndIndexBuffer>(graphicsDevice, vertices, indices, PrimitiveTopology::TriangleList);

    mVertexShader = std::make_unique<VertexShader>(graphicsDevice, "Texture2DVS");
    mPixelShader = std::make_unique<PixelShader>(graphicsDevice, "Texture2DPS");
    mSampler = std::make_unique<Sampler>(graphicsDevice.getDirectX11Device(), TextureAddressMode::Wrap,
        TextureFilterMode::MinMagMipLinear);
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::draw(Sprite2D* sprite) {
    IRenderModeChanger& renderModeChanger = mGraphicsDevice.getRenderModeChanger();

    //�O��̕`��ݒ���ꎞ�I�ɕۑ�
    CullMode preCullMode = renderModeChanger.getCullMode();
    FillMode preFillMode = renderModeChanger.getFillMode();

    //�`��ݒ�
    renderModeChanger.setRenderMode(CullMode::Back, FillMode::Solid);

    //�R���X�^���g�o�b�t�@�̎擾
    ConstantBufferManager& cmanager = mGraphicsDevice.getConstantBufferManager();

    //���_�E�s�N�Z���V�F�[�_
    mVertexShader->set();
    mPixelShader->set();

    //�e�N�X�`���f�[�^
    sprite->getTexture()->setData(ShaderInputType::Pixel, 0);
    mSampler->setData(ShaderInputType::Pixel, 0);

    //���f���E�v���W�F�N�V�����s��̐ݒ�
    cmanager.setMatrix(ConstantBufferParameterType::World, Math::Matrix4x4::transposition(sprite->getModelMatrix()));

    //UV���̐ݒ�
    cmanager.setRect(ConstantBufferParameterType::UV, sprite->getSrcRect());

    //�F�̐ݒ�
    cmanager.setColor(ConstantBufferParameterType::Color, sprite->getColor());

    //�`��
    mVIBuffer->render();

    //�O�̕`��ݒ�ɖ߂�
    renderModeChanger.setRenderMode(preCullMode, preFillMode);
}
} //Graphics 
