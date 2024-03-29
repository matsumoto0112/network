#pragma once

#include <memory>
#include <vector>
#include "Utility/Math/Vector2.h"

namespace Graphics {
class GraphicsDeviceManager;
class TextureChar;

/**
* @class TextureString
* @brief 文字列画像クラス
*/
class TextureString {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @param str 表示する文字列
    * @param fontSize フォントの大きさ
    * @param font フォントの種類
    */
    TextureString(GraphicsDeviceManager& graphicsDevice, const std::string& str, int fontSize, const std::string& font = "");
    /**
    * @brief デストラクタ
    */
    ~TextureString();
    /**
    * @brief 座標の設定
    */
    void setPosition(const Math::Vector2& position);
    /**
    * @brief 座標の取得
    */
    const Math::Vector2& getPosition() const;
    void setString(const std::string& str);
    const std::string& getString() const { return mStr; }
    void setFontSize(int size);
    int getFontSize() const { return mFontSize; }
    void setFont(const std::string& font);
    const std::string& getFont() const { return mFont; }
    /**
    * @brief 描画する
    */
    void draw();
    void setZOrder(float z);
    float getZOrder() const;
private:
    void create();
private:
    GraphicsDeviceManager& mGraphicsDevice;
    std::string mStr;
    int mFontSize;
    std::string mFont;
    Math::Vector2 mPosition;
    std::vector<std::unique_ptr<TextureChar>> mTextureChars; //!< 文字列画像リスト
};

} //Graphics 
