#include "ServerConnectProc.h"
#include "Resources/resource.h"

namespace Window {

ServerConnectProc::ServerConnectProc(ConnectFunc connectFunc)
    :mFunc(connectFunc) {}

ServerConnectProc::~ServerConnectProc() {}

LRESULT ServerConnectProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) {
    if (msg != WM_COMMAND) return 0L;
    if (LOWORD(wParam) != IDC_BUTTON_CONNECT) return 0L;
    *isReturn = TRUE;

    //ポート番号をダイアログから取得
    BOOL flag;
    int port = GetDlgItemInt(hWnd, IDC_EDIT_PORT, &flag, FALSE);
    mFunc(port);

    return 0L;
}

} //Window 
