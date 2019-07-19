#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include <unordered_map>
#include "Device/Graphics/Render/RasterizerMode.h"
#include "Device/Graphics/Render/IRenderModeChanger.h"
#include "Utility/HashCombine.h"

namespace Graphics {
class DirectX11GraphicsDevice;

/**
* @class RasterizerManager
* @brief ラスタライザ管理
*/
class RasterizerManager : public IRenderModeChanger
{
public:
    /**
    * @brief コンストラクタ
    * @param device DirectX11グラフィックデバイス    
    */
    RasterizerManager(DirectX11GraphicsDevice& device);
    /**
    * @brief デストラクタ
    */
    ~RasterizerManager();
    /**
    * @brief 現在のカリングモードの取得
    */
    CullMode getCullMode() const override;
    /**
    * @brief 塗りつぶしモードの取得
    */
    FillMode getFillMode() const override;
    /**
    * @brief 描画モードの設定
    * @param cull カリングの種類
    * @param fill 塗りつぶしの種類
    */
    virtual void setRenderMode(CullMode cull, FillMode fill) override;
private:
    DirectX11GraphicsDevice& mDevice; //!< DirectX11グラフィックデバイス
    std::unordered_map<RasterizerMode, 
        Microsoft::WRL::ComPtr<ID3D11RasterizerState>, 
        RasterizerModeHash, RasterizerModeEqual> mRasStates; //!< 作成済みラスタライザステート
    RasterizerMode mRasterizerMode; //!< 現在のラスタライザの設定
};

} //Graphics 