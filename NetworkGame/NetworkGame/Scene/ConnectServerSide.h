#pragma once

#include <Windows.h>
#include "Scene/ConnectSceneBase.h"

namespace Window {
class IWindowProc;
} //Window 

namespace Network {
class GameServerThread;
} //Network 

namespace Scene {

/**
* @class ConnectServerSide
* @brief �T�[�o�[���̃N���C�A���g�ڑ��V�[��
*/
class ConnectServerSide :public ConnectSceneBase {
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
    std::unique_ptr<Network::GameServerThread> mServerThread; //!< �T�[�o�[�X���b�h
    Window::IWindowProc* mConnectEventProc;
    Window::IWindowProc* mConnectCancelEventProc;
};

} //Scene 