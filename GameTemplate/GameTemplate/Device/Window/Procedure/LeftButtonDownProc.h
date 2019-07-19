#pragma once

#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class LeftButtonDownProc
* @brief discription
*/
class LeftButtonDownProc :public IWindowProc {
    using ClickFunc = std::function<void(void)>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    LeftButtonDownProc(ClickFunc left);
    /**
    * @brief �f�X�g���N�^
    */
    ~LeftButtonDownProc();
    // IWindowProc ����Čp������܂���
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
private:
    ClickFunc mLeftClick;
};

} //Window 