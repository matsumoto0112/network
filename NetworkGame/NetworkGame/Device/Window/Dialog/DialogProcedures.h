#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class DialogProcedures
* @brief ダイアログのプロシージャ管理クラス
*/
class DialogProcedures {
public:
    /**
    * @brief クライアント用ダイアログプロシージャ
    */
    static BOOL CALLBACK ClientDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    /**
    * @brief サーバー用ダイアログプロシージャ
    */
    static BOOL CALLBACK ServerDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
private:
    using WindowProcPtr = std::unique_ptr<IWindowProc>;
    using WindowProcContainer = std::vector<WindowProcPtr>;
public:
    static WindowProcContainer mClientDlgProc; //!< クライアント用プロシージャリスト
    static WindowProcContainer mServerDlgProc; //!< サーバー用プロシージャリスト
};

} //Window 