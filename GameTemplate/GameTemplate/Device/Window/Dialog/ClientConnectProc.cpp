#include "ClientConnectProc.h"
#include "Resources/resource.h"

namespace Window {
ClientConnectProc::ClientConnectProc(ConnectFunc connectFunc)
    :mFunc(connectFunc) {}

ClientConnectProc::~ClientConnectProc() {}

LRESULT ClientConnectProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    if (msg != WM_COMMAND) return 0L;
    if (LOWORD(wParam) != IDC_BUTTON_CONNECT) return 0L;
    *isReturn = TRUE;
    //アドレスとポート番号をダイアログから取得する
    std::string address;
    GetDlgItemText(hWnd, IDC_EDIT_SERVER, &address[0], 1024);
    BOOL flag;
    int port = GetDlgItemInt(hWnd, IDC_EDIT_PORT, &flag, FALSE);
    mFunc(address, port);
    return 0L;
}

} //Window 
