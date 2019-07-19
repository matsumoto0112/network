#pragma once

#include <string>
#include "Device/Graphics/Shader/ShaderBase.h"
#include "Device/Graphics/Shader/PixelShaderData.h"

namespace Graphics {
class GraphicsDeviceManager;

/**
* @class PixelShader
* @brief ピクセルシェーダ
*/
class PixelShader : public ShaderBase {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @param filename シェーダファイル名
    */
    PixelShader(GraphicsDeviceManager& graphicsDevice, const std::string& filename);
    /**
    * @brief デストラクタ
    */
    ~PixelShader();
    /**
    * @brief ピクセルシェーダのセット
    */
    void set();
private:
    /**
    * @brief ピクセルシェーダの作成
    * @param name シェーダファイル名
    */
    void create(const std::string& name);
private:
    std::unique_ptr<PixelShaderData> mShaderData; //!< シェーダーのデータ
};

} //Graphics 
