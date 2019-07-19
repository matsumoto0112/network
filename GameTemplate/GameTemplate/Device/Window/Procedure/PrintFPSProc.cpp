#include "PrintFPSProc.h"
#include "Resources/resource.h"

namespace Window {

PrintFPSProc::PrintFPSProc(HWND hWnd, PrintFunc func)
    :mFunc(func), mMenuCheckedController(hWnd, ID_PRINT_FPS) {}

PrintFPSProc::~PrintFPSProc() {}

LRESULT PrintFPSProc::wndProc(HWND hWnd, UINT msg,
    WPARAM wParam, LPARAM lParam, BOOL* isReturn) {

    if (msg != WM_COMMAND) return 0L;

    switch (LOWORD(wParam)) {
    case ID_PRINT_FPS:
        *isReturn = TRUE;
        mMenuCheckedController.switchCheckFlag();
        mFunc();
        break;
    }
    return 0L;
}

} //Window 
