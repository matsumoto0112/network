#pragma once

#include <string>
#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class ServerConnectProc
* @brief �T�[�o�[���Őڑ��{�^���������ꂽ�Ƃ��̃v���V�[�W��
*/
class ServerConnectProc :public IWindowProc {
    using ConnectFunc = std::function<void(int)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param connectFunc �ڑ��{�^���������ꂽ�Ƃ��̃C�x���g
    */
    ServerConnectProc(ConnectFunc connectFunc);
    /**
    * @brief �f�X�g���N�^
    */
    ~ServerConnectProc();
    /**
    * @brief �v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) override;
private:
    ConnectFunc mFunc; //!< �ڑ��{�^���������ꂽ�Ƃ��̃C�x���g�֐�
};
} //Window 