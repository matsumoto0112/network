#include "ShowCursorProc.h"
#include "Resources/resource.h"
#include <iostream>

namespace Window {

ShowCursorProc::ShowCursorProc(HWND hWnd, CursorEvent showEvent, CursorEvent hideEvent)
    :mMenuCheckedController(hWnd, ID_SHOWCURSOR) {
    bool show = mMenuCheckedController.isChecked();

    //show/hideÉCÉxÉìÉgÇåƒÇ‘ä÷êîçÏê¨
    mEvent = [showEvent, hideEvent](bool show) {if (show)showEvent(); else hideEvent(); };
    mEvent(show);
}

ShowCursorProc::~ShowCursorProc() {}

LRESULT ShowCursorProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) {
    if (msg != WM_COMMAND)return 0L;
    switch (LOWORD(wParam)) {
    case ID_SHOWCURSOR:
        *isReturn = true;
        mMenuCheckedController.switchCheckFlag();
        bool check = mMenuCheckedController.isChecked();

        mEvent(check);
        break;
    }
    return 0L;
}

} //Window 
