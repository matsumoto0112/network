#include "InitProc.h"

namespace Window {

InitProc::InitProc() {}

InitProc::~InitProc() {}

LRESULT InitProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    if (msg != WM_INITDIALOG)return FALSE;
    *isReturn = TRUE;
    return TRUE;
}
} //Window 
