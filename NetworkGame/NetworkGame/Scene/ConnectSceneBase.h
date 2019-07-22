#pragma once
#include "Scene/IScene.h"

namespace Window {
class DialogWindow;
} //Window 

namespace Graphics {
class TextureString;
} //Graphics 

namespace Scene {

/**
* @class ConnectSceneBase
* @brief 接続待機基底シーン
*/
class ConnectSceneBase : public IScene {
public:
    /**
    * @brief コンストラクタ
    */
    ConnectSceneBase(Window::DialogWindow& dialogWindow);
    /**
    * @brief デストラクタ
    */
    virtual ~ConnectSceneBase();

    virtual void update(float delta) override;

    virtual bool isEndScene() const override;

    virtual void draw() override;
protected:
    bool mIsSceneEnd;
    bool mIsSelectConnect; //!< 接続を選択したか
    Window::DialogWindow& mDialogWindow;
    std::unique_ptr<Graphics::TextureString> mMessage;
};

} //Scene 