#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include "Scene/ConnectSceneBase.h"

namespace Window {
class IWindowProc;
} //Window 

namespace Network {
class GameClientThread;
} //Network 

namespace Scene {

/**
* @class ConnectClientSide
* @brief �N���C�A���g���̃T�[�o�[�ڑ��V�[��
*/
class ConnectClientSide : public ConnectSceneBase {
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
    void pushConnectButton(const std::string& address, int port);
private:
    std::unique_ptr<Network::GameClientThread> mClient; //!< �N���C�A���g�X���b�h
    Window::IWindowProc* mConnectEventProc;
    Window::IWindowProc* mConnectCancelEventProc;
};

} //Scene 