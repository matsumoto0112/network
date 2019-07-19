#include "GraphicsDeviceManager.h"
#include <assert.h>
#include <vector>
#include <memory>
#include <algorithm>
#include "Utility/Debug.h"
#include "Utility/Math/Vector2.h"
#include "Device/Graphics/Sprite/SpriteRenderer.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"

#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/Primitive/PrimitiveDataStorage.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"
#include <dxgi1_2.h>
#include "Device/Graphics/Render/DepthStencilView.h"
#include "Device/Graphics/Render/RenderTargetManager.h"
#include "Device/Graphics/Render/AlphaBlend.h"
#include "Device/Graphics/Render/RasterizerManager.h"
#include "Device/Graphics/Texture/Sampler.h"
#include "Device/Graphics/Shader/ShaderInputType.h"

#include "Vertex/Vertex.h"
#include "Buffer/VertexAndIndexBuffer.h"
#include "Device/Graphics/Shader/PixelShader.h"
#include "Device/Graphics/Texture/Texture.h"
#include "Device/Graphics/Shader/VertexShader.h"
#include "Device/Graphics/Buffer/Constant/ConstantBuffer.h"
#include "Define/Window.h"
#include "Device/Graphics/Render/RenderTarget.h"
#include "Device/Graphics/Render/RenderTargetView.h"
#include "Device/Graphics/Texture/TextureBuffer.h"
#include "Device/Graphics/Shader/ShaderResourceView.h"
#include "Device/Graphics/Render/Viewport.h"
#include "Device/Graphics/Light/LightManager.h"

#include "Device/Graphics/Render/RenderTargetFactory.h"

namespace Graphics {

GraphicsDeviceManager::GraphicsDeviceManager() {}
GraphicsDeviceManager::~GraphicsDeviceManager() {}

bool GraphicsDeviceManager::init(HWND hWnd, const Vec2& screenSize, bool isFullScreen) {
    mScreenSize = screenSize;

    mGraphicsDevice = std::make_unique<DirectX11GraphicsDevice>(hWnd,
        (UINT)screenSize.x, (UINT)screenSize.y, isFullScreen);

    Microsoft::WRL::ComPtr<ID3D11DeviceContext> mImmediateContext = mGraphicsDevice->getContext();

    mAlphaBlend = std::make_unique<AlphaBlend>(*mGraphicsDevice);
    mRasterizerManager = std::make_unique<RasterizerManager>(*mGraphicsDevice);

    mSpriteRenderer = std::make_unique<SpriteRenderer>(*this);
    mConstantBufferManager = std::make_unique<ConstantBufferManager>(*mGraphicsDevice);
    mPrimitiveDataStorage = std::make_unique<PrimitiveDataStorage>(*this);

    mLightManager = std::make_unique<LightManager>(*this);
    mDefaultSampler = std::make_unique<Sampler>(*mGraphicsDevice, TextureAddressMode::Clamp, TextureFilterMode::MinMagMipLinear);
    //バックバッファはテクスチャを作成できないため第三引数にfalseを指定
    auto mBackView = std::make_unique<RenderTargetView>(*this, mGraphicsDevice->getBackBuffer(), false);

    Viewport vp(mScreenSize);
    auto mDefaultRT = std::make_unique<RenderTarget>(*mGraphicsDevice,
        vp, std::move(mBackView), nullptr);

    //デフォルトのバックバッファを挿入
    mRenderTargetManager = std::make_unique<RenderTargetManager>(std::move(mDefaultRT));
    return true;
}

void GraphicsDeviceManager::cleanupDevice() {}

void GraphicsDeviceManager::drawBegin() {
    //全部の初期化
    ID3D11DeviceContext* context = mGraphicsDevice->getContext().Get();
    context->ClearState();

    //ラスタライザのデフォルト設定
    mRasterizerManager->setRenderMode(CullMode::Back, FillMode::Solid);
    //アルファブレンドの設定
    mAlphaBlend->set();
    //デフォルトの描画出力先に変更
    mRenderTargetManager->setActiveRenderTarget(0);
    mDefaultSampler->setData(ShaderInputType::Pixel, 0);
    mLightManager->set();
}

void GraphicsDeviceManager::drawEnd() {
    ID3D11DeviceContext* context = mGraphicsDevice->getContext().Get();

    //最初に初期化をする
    ID3D11ShaderResourceView* nullSrvs[4] = { nullptr,nullptr,nullptr,nullptr };
    context->PSSetShaderResources(0, 4, nullSrvs);

    ID3D11RenderTargetView* nullRtvs[2] = { nullptr,nullptr };
    context->OMSetRenderTargets(2, nullRtvs, nullptr);

    //カメラのレンダリング結果を描画
    CameraManager::getInstance().render();

    //バックバッファと入れ替える
    mGraphicsDevice->present();
    //最後に初期化
    context->PSSetShaderResources(0, 4, nullSrvs);
    context->OMSetRenderTargets(2, nullRtvs, nullptr);
}

Microsoft::WRL::ComPtr<ID3D11Device> GraphicsDeviceManager::getDevice() const {
    return mGraphicsDevice->getDevice();
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> GraphicsDeviceManager::getContext() const {
    return mGraphicsDevice->getContext();
}

IRenderModeChanger& GraphicsDeviceManager::getRenderModeChanger() const {
    return *mRasterizerManager;
}

} //Graphics 
