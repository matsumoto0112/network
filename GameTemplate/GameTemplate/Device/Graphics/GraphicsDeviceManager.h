#pragma once

#include <array>
#include <memory>
#include <wrl/client.h>
#include <unordered_map>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dCompiler.lib")
#include <d3d11.h>
#include "Utility/Math/Vector2.h"
#include "Device/Graphics/Color4.h"

namespace Graphics {

class SpriteRenderer;
class ConstantBufferManager;
class ConstantBufferManager;
class PrimitiveDataStorage;
class DirectX11GraphicsDevice;
class RenderTargetManager;
class AlphaBlend;
class IRenderModeChanger;
class RasterizerManager;
class LightManager;
class Sampler;

/**
* @class GraphicsDeviceManager
*/
class GraphicsDeviceManager {
    using Vec2 = Math::Vector2;
public:
    /**
    * @brief コンストラクタ
    */
    GraphicsDeviceManager();
    /**
    * @brief デストラクタ
    */
    ~GraphicsDeviceManager();
    /**
    * @brief 初期化
    * @param hWnd ウィンドウハンドル
    * @param screenSize ウィンドウの大きさ
    * @param isFullScreen フルスクリーンか？
    */
    bool init(HWND hWnd, const Vec2& screenSize, bool isFullScreen);
    /**
    * @brief デバイスの終了処理
    */
    void cleanupDevice();
    /**
    * @brief 描画開始
    */
    void drawBegin();
    /**
    * @brief 描画終了
    */
    void drawEnd();
    /**
    * @brief デバイスの取得
    */
    Microsoft::WRL::ComPtr<ID3D11Device> getDevice() const;
    /**
    * @brief デバイスコンテキストの取得
    */
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getContext() const;
    /**
    * @brief スプライト描画器の取得
    */
    SpriteRenderer& getSpriteRenderer() const { return *mSpriteRenderer; }
    /**
    * @brief コンスタントバッファ管理者の取得
    */
    ConstantBufferManager& getConstantBufferManager() const { return *mConstantBufferManager; }
    /**
    * @brief プリミティブ管理者の取得
    */
    PrimitiveDataStorage& getPrimtiveStorage() const { return *mPrimitiveDataStorage; }
    /**
    * @brief レンダーターゲットの管理者の取得
    */
    RenderTargetManager& getRenderTargetManager() const { return *mRenderTargetManager; }

    LightManager& getLightManager() const { return *mLightManager; }

    /**
    * @brief スクリーンサイズの取得
    */
    const Vec2& getScreenSize() const { return mScreenSize; }
    /**
    * @brief 描画モード変更器の取得
    */
    IRenderModeChanger& getRenderModeChanger() const;
    /**
    * @brief DirectX11用グラフィックデバイスの取得
    */
    DirectX11GraphicsDevice& getDirectX11Device() const { return *mGraphicsDevice.get(); }
private:
    std::unique_ptr<DirectX11GraphicsDevice> mGraphicsDevice; //!< DirectX11用グラフィックデバイス
    std::unique_ptr<RenderTargetManager> mRenderTargetManager; //!< レンダーターゲットの管理者
    std::unique_ptr<AlphaBlend> mAlphaBlend; //!< アルファブレンド
    std::unique_ptr<RasterizerManager> mRasterizerManager; //!< ラスタライザ管理
    std::unique_ptr<SpriteRenderer> mSpriteRenderer; //!< スプライト描画器
    std::unique_ptr<ConstantBufferManager> mConstantBufferManager; //!< コンスタントバッファ管理者
    std::unique_ptr<PrimitiveDataStorage> mPrimitiveDataStorage; //!< プリミティブ描画オブジェクト保存
    std::unique_ptr<LightManager> mLightManager;
    std::unique_ptr<Sampler> mDefaultSampler; //!< デフォルトのサンプラー
    Vec2 mScreenSize; //!< スクリーンの大きさ
};
} //Graphics 