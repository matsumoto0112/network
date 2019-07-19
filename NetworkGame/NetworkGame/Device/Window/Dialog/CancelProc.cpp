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
    //ダイアログの終了メッセージを送る
    PostMessage(hWnd, WM_CLOSE, 0, 0);
    return 0L;
}

} //Window 
