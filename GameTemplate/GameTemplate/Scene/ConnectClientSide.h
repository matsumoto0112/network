#pragma once

#include "Scene/IScene.h"
#include <Windows.h>
#include <memory>
#include <string>

namespace Network {
class GameClientThread;
} //Network 

namespace Graphics {
class TextureString;
} //Graphics 

namespace Scene {

/**
* @class ConnectClientSide
* @brief �N���C�A���g���̃T�[�o�[�ڑ��V�[��
*/
class ConnectClientSide :public IScene {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ConnectClientSide();
    /**
    * @brief �f�X�g���N�^
    */
    ~ConnectClientSide();
    /**
    * @brief �X�V
    * @param delta �O�t���[������̍�������
    */
    virtual void update(float delta) override;
    /**
    * @brief �V�[�����I�����Ă��邩
    */
    virtual bool isEndScene() const override;
    /**
    * @brief �`��
    */
    virtual void draw() override;
    /**
    * @brief �I��������
    * @return ���̃V�[��
    */
    virtual std::unique_ptr<IScene> end() override;
private:
    /**
    * @brief �ڑ��{�^���������ꂽ�Ƃ��̃C�x���g
    * @param address �T�[�o�[�A�h���X
    * @param port �|�[�g�ԍ�
    */
    void pushConnectButton(const std::string& address,int port);
private:
    bool mIsSceneEnd; //!< �V�[�����I�����Ă��邩 
    bool mIsSelectConnect; //!< �ڑ��������ꂽ��
    HWND mDlg; //!< �_�C�A���O�n���h��
    std::unique_ptr<Graphics::TextureString> mStr; //!< �\������UI������
    std::unique_ptr<Network::GameClientThread> mClient; //!< �N���C�A���g�X���b�h
};

} //Scene 