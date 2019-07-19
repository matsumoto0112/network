#include "CameraManager.h"
#include "Device/Graphics/Camera/PerspectiveCamera.h"
#include "Device/Graphics/Camera/OrthographicCamera.h"
#include "Device/Graphics/Shader/Effect.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferTypeManager.h"
#include "Utility/Debug.h"
#include "Device/GameDevice.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Render/RenderTargetManager.h"
#include "Device/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/Camera/Camera.h"
#include "Define/Render/Camera.h"
#include "Define/Window.h"
#include "Device/Graphics/Primitive/Quad2D.h"
#include "Utility/Resource/ResourceManager.h"
#include "Device/GameDevice.h"

namespace Graphics {

CameraManager::CameraManager()
    : mGraphicsDevice(Device::GameDevice::getInstance().getDirectX11Device()),
    mQuad(std::make_unique<Quad2D>(mGraphicsDevice,
        Math::AABB2D(Math::Vector2(0.0f, 0.0f), Define::Window::getSize()))),
    mBlendEffect(std::make_unique<Effect>(
        Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Default2D),
        Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Blend))) {}

CameraManager::~CameraManager() {
    mCameras.clear();
}

void CameraManager::addCamera(Define::CameraType type, std::unique_ptr<Camera> camera) {
    MY_ASSERTION(mCameras.find(type) == mCameras.end(),
        "既に登録済みのカメラが再登録されました。");
    mCameras.emplace(type, std::move(camera));
}

void CameraManager::setRenderingCamera(Define::CameraType type) {
    MY_ASSERTION(mCameras.find(type) != mCameras.end(),
        Utility::StringBuilder("") << (UINT)type << "が存在しません");
    mCameras[type]->setActiveRenderingCamera();
}

void CameraManager::render() {
    Math::Matrix4x4 view = Math::Matrix4x4::identity();
    Math::Matrix4x4 proj = Math::Matrix4x4::createOrthographic(Define::Window::getSize());
    Graphics::ConstantBufferManager& cbManager = mGraphicsDevice.getConstantBufferManager();
    cbManager.setMatrix(ConstantBufferParameterType::View, view);
    cbManager.setMatrix(ConstantBufferParameterType::Projection, Math::Matrix4x4::transposition(proj));

    for (auto&& camera : mCameras) {
        camera.second->postEffect();
    }

    ID3D11DeviceContext* context = mGraphicsDevice.getContext().Get();
    //最初に初期化をする
    ID3D11ShaderResourceView* nullSrvs[4] = { nullptr,nullptr,nullptr,nullptr };

    ID3D11RenderTargetView* nullRtvs[2] = { nullptr,nullptr };
    context->PSSetShaderResources(0, 4, nullSrvs);
    context->OMSetRenderTargets(2, nullRtvs, nullptr);

    //描画対象をデフォルトに切り替え
    //有効カメラの数をカウントする
    int cnt = 0;
    for (auto&& camera : mCameras) {
        //アクティブ状態でなければスルー
        if (!camera.second->isActive())continue;
        //有効カメラならシェーダーにテクスチャを転送する
        //その際の番号は有効カメラの先頭から何番目かで決まる
        camera.second->setShaderResource(cnt);
        cnt++;
    }

    mGraphicsDevice.getRenderTargetManager().setActiveRenderTarget(0);
    MY_ASSERTION(cnt < Define::Camera::CAMERA_SYNTHESIS_NUM + 1,
        "レンダリング状態のカメラが多すぎます。");

    mBlendEffect->set();
    //有効カメラ数をコンスタントバッファに転送
    cbManager.setInt(ConstantBufferParameterType::CameraNum, cnt);
    cbManager.send();

    //2Dワールド行列の転送
    Math::Rect uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    cbManager.setRect(ConstantBufferParameterType::UV, uvRect);
    cbManager.setMatrix(ConstantBufferParameterType::View, view);
    cbManager.setMatrix(ConstantBufferParameterType::Projection, Math::Matrix4x4::transposition(proj));
    mQuad->render();

    for (auto&& camera : mCameras) {
        camera.second->clearRenderTarget();
    }
}

} //Graphics 
