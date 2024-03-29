#include "CancelProc.h"
#include "Resources/resource.h"

namespace Window {
CancelProc::CancelProc(CancelFunc cancelFunc)
    :mFunc(cancelFunc) {}

CancelProc::~CancelProc() {}

LRESULT CancelProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    if (msg != WM_COMMAND)return FALSE;
    if (LOWORD(wParam) != IDC_BUTTON_CANCEL) return FALSE;
    *isReturn = TRUE;
    mFunc();
    //ダイアログの終了メッセージを送る
    PostMessage(hWnd, WM_CLOSE, 0, 0);
    return TRUE;
}

} //Window 
