#include "ClientConnectProc.h"
#include "Resources/resource.h"

namespace Window {
ClientConnectProc::ClientConnectProc(ConnectFunc connectFunc)
    :mFunc(connectFunc) {}

ClientConnectProc::~ClientConnectProc() {}

LRESULT ClientConnectProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    if (msg != WM_COMMAND) return FALSE;
    if (LOWORD(wParam) != IDC_BUTTON_CONNECT) return FALSE;
    *isReturn = TRUE;
    //�A�h���X�ƃ|�[�g�ԍ����_�C�A���O����擾����
    std::string address;
    GetDlgItemText(hWnd, IDC_EDIT_SERVER, &address[0], 1024);
    BOOL flag;
    int port = GetDlgItemInt(hWnd, IDC_EDIT_PORT, &flag, FALSE);
    mFunc(address, port);
    return TRUE;
}

} //Window 
