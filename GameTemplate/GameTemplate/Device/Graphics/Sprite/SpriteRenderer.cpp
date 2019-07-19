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

    //前回の描画設定を一時的に保存
    CullMode preCullMode = renderModeChanger.getCullMode();
    FillMode preFillMode = renderModeChanger.getFillMode();

    //描画設定
    renderModeChanger.setRenderMode(CullMode::Back, FillMode::Solid);

    //コンスタントバッファの取得
    ConstantBufferManager& cmanager = mGraphicsDevice.getConstantBufferManager();

    //頂点・ピクセルシェーダ
    mVertexShader->set();
    mPixelShader->set();

    //テクスチャデータ
    sprite->getTexture()->setData(ShaderInputType::Pixel, 0);
    mSampler->setData(ShaderInputType::Pixel, 0);

    //モデル・プロジェクション行列の設定
    cmanager.setMatrix(ConstantBufferParameterType::World, Math::Matrix4x4::transposition(sprite->getModelMatrix()));

    //UV情報の設定
    cmanager.setRect(ConstantBufferParameterType::UV, sprite->getSrcRect());

    //色の設定
    cmanager.setColor(ConstantBufferParameterType::Color, sprite->getColor());

    //描画
    mVIBuffer->render();

    //前の描画設定に戻す
    renderModeChanger.setRenderMode(preCullMode, preFillMode);
}
} //Graphics 
