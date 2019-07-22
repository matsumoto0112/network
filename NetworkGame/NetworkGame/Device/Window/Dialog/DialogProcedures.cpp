#include "DialogProcedures.h"

namespace Window {

std::vector<std::unique_ptr<IWindowProc>>
DialogProcedures::mClientDlgProc = std::vector<std::unique_ptr<IWindowProc>>();
std::vector<std::unique_ptr<IWindowProc>>
DialogProcedures::mServerDlgProc = std::vector<std::unique_ptr<IWindowProc>>();

BOOL DialogProcedures::ClientDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp) {
    BOOL isReturn = FALSE;
    //先頭から順にプロシージャが処理されるまでループ
    for (auto&& proc : mClientDlgProc) {
        LRESULT res = proc->wndProc(hDlg, msg, wp, lp, &isReturn);
        if (isReturn)return res;
    }
    return FALSE;
}

BOOL DialogProcedures::ServerDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp) {
    BOOL isReturn = FALSE;
    //先頭から順にプロシージャが処理されるまでループ
    for (auto&& proc : mServerDlgProc) {
        LRESULT res = proc->wndProc(hDlg, msg, wp, lp, &isReturn);
        if (isReturn)return res;
    }
    return FALSE;
}

} //Window 
