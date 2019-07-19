#include "EndProc.h"
#include "Resources/resource.h"

namespace Window {

EndProc::~EndProc() {}

LRESULT EndProc::wndProc(HWND hWnd, UINT msg,
    WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    if (msg != WM_COMMAND) return 0L;
    switch (LOWORD(wParam)) {
    case ID_END:
        *isReturn = TRUE;
        SendMessage(hWnd, WM_CLOSE, 0, 0);
        break;
    }
    return 0L;
}

} //Window 
