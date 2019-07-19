#include "MenuCheckedController.h"

namespace Window {

MenuCheckedController::MenuCheckedController(HWND hWnd, UINT itemID)
    :mItemID(itemID) {
    mHMenu = GetMenu(hWnd);
    UINT state = GetMenuState(mHMenu, itemID, MF_BYCOMMAND);
    mIsChecked = (state & MFS_CHECKED) ? true : false;
}

MenuCheckedController::~MenuCheckedController() {}

bool MenuCheckedController::isChecked() const {
    return mIsChecked;
}

void MenuCheckedController::setChecked(bool checked) {
    mIsChecked = checked;
    updateCheck();
}

void MenuCheckedController::switchCheckFlag() {
    mIsChecked = !mIsChecked;
    updateCheck();
}

void MenuCheckedController::updateCheck() {
    UINT state = mIsChecked ? MFS_CHECKED : MFS_UNCHECKED;
    CheckMenuItem(mHMenu, mItemID, MF_BYCOMMAND | state);
}

} //Window 
