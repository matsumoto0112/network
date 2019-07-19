#include "LeftButtonDownProc.h"
#include "Utility/Debug.h"
#include <iostream>

namespace Window {


LeftButtonDownProc::LeftButtonDownProc(ClickFunc left)
    :mLeftClick(left) {}

LeftButtonDownProc::~LeftButtonDownProc() {}

LRESULT LeftButtonDownProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) {
    if (msg != WM_LBUTTONDOWN)return 0L;
    MY_ASSERTION(mLeftClick != nullptr, "���N���b�N���ꂽ�Ƃ��̃C�x���g������`�ł�");
    *isReturn = TRUE;
    mLeftClick();
    std::cout << "click!\n";
    return 0L;
}
} //Window 
