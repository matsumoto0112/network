#pragma once

#include "Scene/IScene.h"
#include <Windows.h>

namespace Network {
class GameServerThread;
} //Network 

namespace Graphics {
class TextureString;
} //Graphics 

namespace Scene {

/**
* @class ConnectServerSide
* @brief �T�[�o�[���̃N���C�A���g�ڑ��V�[��
*/
class ConnectServerSide :public IScene {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ConnectServerSide();
    /**
    * @brief �f�X�g���N�^
    */
    ~ConnectServerSide();
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
    * @param port �|�[�g�ԍ�
    */
    void puchConnectButton(int port);
private:
    bool mIsSceneEnd; //!< �V�[�����I�����Ă��邩
    bool mIsSelectConnect; //!< �ڑ���I��������
    HWND mDlg; //!< �_�C�A���O�n���h��
    std::unique_ptr<Graphics::TextureString> mStr; //!< �\������UI������
    std::unique_ptr<Network::GameServerThread> mServerThread; //!< �T�[�o�[�X���b�h
};

} //Scene 