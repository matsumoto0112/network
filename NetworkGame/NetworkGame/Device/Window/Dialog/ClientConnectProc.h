#pragma once

#include <string>
#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class ClientConnectProc
* @brief �N���C�A���g���Őڑ��{�^���������ꂽ�Ƃ��̃v���V�[�W��
*/
class ClientConnectProc :public IWindowProc {
    using ConnectFunc = std::function<void(const std::string& ,int)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param connectFunc �{�^���������ꂽ�Ƃ��̃C�x���g
    */
    ClientConnectProc(ConnectFunc connectFunc);
    /**
    * @brief �f�X�g���N�^
    */
    ~ClientConnectProc();
    /**
    * @brief �v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) override;
private:
    ConnectFunc mFunc; //!< �{�^���������ꂽ�Ƃ��̃C�x���g�֐�
};
} //Window 