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
* @brief �ڑ��ҋ@���V�[��
*/
class ConnectSceneBase : public IScene {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ConnectSceneBase(Window::DialogWindow& dialogWindow);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ConnectSceneBase();

    virtual void update(float delta) override;

    virtual bool isEndScene() const override;

    virtual void draw() override;
protected:
    bool mIsSceneEnd;
    bool mIsSelectConnect; //!< �ڑ���I��������
    Window::DialogWindow& mDialogWindow;
    std::unique_ptr<Graphics::TextureString> mMessage;
};

} //Scene 