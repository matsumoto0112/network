#pragma once

#include "Device/Graphics/Render/RasterizerMode.h"

namespace Graphics {

/**
* @class IRenderModeChanger
* @brief 描画モード変更インターフェース
*/
class IRenderModeChanger
{
public:
    /**
    * @brief 仮想デストラクタ
    */
    virtual ~IRenderModeChanger() = default;
    /**
    * @brief 描画モードの設定
    * @param cull カリングの設定
    * @param fill 塗りつぶしの設定
    */
    virtual void setRenderMode(CullMode cull, FillMode fill) = 0;
    /**
    * @brief 現在のカリングモードの取得
    */
    virtual CullMode getCullMode() const = 0;
    /**
    * @brief 塗りつぶしモードの取得
    */
    virtual FillMode getFillMode() const = 0;
};

} //Graphics 
