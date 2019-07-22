#include "DialogWindow.h"
#include "Device/Window/Window.h"
#include "Device/GameDevice.h"

namespace Window {

DialogWindow::DialogWindow(Window* parentWindow, UINT dialogID, DLGPROC dlgProc) :
    mIsEnd(false) {
    HWND hWnd = parentWindow ? parentWindow->getHWND() : NULL;
    mDlgHandle = CreateDialog(
        (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
        MAKEINTRESOURCE(dialogID),
        hWnd,
        dlgProc);

    ShowWindow(mDlgHandle, SW_SHOW);
}

DialogWindow::~DialogWindow() {
    mDlgHandle = NULL;
}

void DialogWindow::close() {
    mIsEnd = true;
    PostMessage(mDlgHandle, WM_CLOSE, 0, 0);
}

} //Window 
