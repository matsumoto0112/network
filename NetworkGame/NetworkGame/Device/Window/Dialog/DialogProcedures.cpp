#include "DialogProcedures.h"
#include <algorithm>

namespace Window {

std::unordered_map<DialogProcType, DialogProcedures::WindowProcContainer>
DialogProcedures::mProceduresContainer = std::unordered_map<DialogProcType, DialogProcedures::WindowProcContainer>();

BOOL DialogProcedures::ClientDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp) {
    BOOL isReturn = FALSE;
    //先頭から順にプロシージャが処理されるまでループ
    for (auto&& proc : mProceduresContainer[DialogProcType::Client]) {
        LRESULT res = proc->wndProc(hDlg, msg, wp, lp, &isReturn);
        if (isReturn)return res;
    }
    return FALSE;
}

BOOL DialogProcedures::ServerDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp) {
    BOOL isReturn = FALSE;
    //先頭から順にプロシージャが処理されるまでループ
    for (auto&& proc : mProceduresContainer[DialogProcType::Server]) {
        LRESULT res = proc->wndProc(hDlg, msg, wp, lp, &isReturn);
        if (isReturn)return res;
    }
    return FALSE;
}

IWindowProc* DialogProcedures::addProcedure(DialogProcType type, IWindowProc* proc) {
    mProceduresContainer[type].emplace_back(std::unique_ptr<IWindowProc>(proc));
    return mProceduresContainer[type].back().get();
}

void DialogProcedures::removeProcedure(DialogProcType type, IWindowProc* procIt) {
    auto removeIt = std::remove_if(mProceduresContainer[type].begin(), mProceduresContainer[type].end(),
        [&](auto&& proc) {return proc.get() == procIt; });
    mProceduresContainer[type].erase(removeIt, mProceduresContainer[type].end());
}



} //Window 
