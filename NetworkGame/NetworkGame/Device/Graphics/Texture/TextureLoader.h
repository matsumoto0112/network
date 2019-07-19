#pragma once

#include <wincodec.h>
#include <memory>
#include <string>
#include <d3d11.h>

namespace Graphics {
class GraphicsDeviceManager;
class ResourceStructureManager;
class Texture;

/**
* @class TextureLoader
* @brief テクスチャ読み込み機
*/
class TextureLoader
{
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    */
    TextureLoader(GraphicsDeviceManager& graphicsDevice);
    /**
    * @brief デストラクタ
    */
    ~TextureLoader();
    /**
    * @brief テクスチャ読み込み
    * @param filepath ファイルへのパス
    */
    std::unique_ptr<Texture> load(const std::string& filepath);
private:
    GraphicsDeviceManager& mGraphicsDevice; //!< グラフィックデバイス
    IWICBitmapDecoder* mDecoder; //!< デコーダー
    IWICBitmapFrameDecode* mFrame; //!< フレームデコード
    IWICFormatConverter* mConverter; //!< フォーマット変換器
    IWICImagingFactory* mFactory; //!< イメージ生成器
    D3D11_TEXTURE2D_DESC mTexture2DDesc; //!< テクスチャ2Dデスク
    D3D11_SHADER_RESOURCE_VIEW_DESC mSRVDesc; //!< シェーダーリソースビューデスク
};

} //Graphics 
