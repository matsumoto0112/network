#pragma once

#include <wrl/client.h>
#include <d3d11.h>

namespace Graphics {

class DirectX11GraphicsDevice;

/**
* @class DepthStencilView
* @brief 深度・ステンシルビュー
*/
class DepthStencilView {
public:
    /**
    * vコンストラクタ
    * @param device DirectX11グラフィックデバイス
    * @param backBufferWidth バックバッファの幅
    * @param backBufferHeight バックバッファの高さ
    * @param count ピクセル単位のマルチサンプリング数
    * @param quality イメージの品質レベル
    */
    DepthStencilView(DirectX11GraphicsDevice& device,
        UINT backBufferWidth, UINT backBufferHeight,
        UINT count = 1, UINT quality = 0);
    /**
    * @brief デストラクタ
    */
    ~DepthStencilView();
    /**
    * @brief バッファの取得
    */
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> getView() const;
    /**
    * @brief バッファのクリア
    */
    void clear();
private:
    DirectX11GraphicsDevice& mDevice; //!< DirectX11グラフィックデバイス
    Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencil; //!< 深度・ステンシルバッファ用テクスチャ
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView; //!< 深度・ステンシルバッファ
};
} //Graphics 