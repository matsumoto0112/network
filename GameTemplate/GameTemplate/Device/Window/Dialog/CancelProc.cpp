#include "CancelProc.h"
#include "Resources/resource.h"

namespace Window {
CancelProc::CancelProc(CancelFunc cancelFunc)
    :mFunc(cancelFunc) {}

CancelProc::~CancelProc() {}

LRESULT CancelProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    if (msg != WM_COMMAND)return 0L;
    if (LOWORD(wParam) != IDC_BUTTON_CANCEL) return 0L;
    *isReturn = TRUE;
    mFunc();
    //�_�C�A���O�̏I�����b�Z�[�W�𑗂�
    PostMessage(hWnd, WM_CLOSE, 0, 0);
    return 0L;
}

} //Window 
