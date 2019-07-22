#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {
enum class DialogProcType {
    Client,
    Server,
};

/**
* @class DialogProcedures
* @brief ダイアログのプロシージャ管理クラス
*/
class DialogProcedures {
private:
    using WindowProcPtr = std::unique_ptr<IWindowProc>;
    using WindowProcContainer = std::vector<WindowProcPtr>;
public:
    /**
    * @brief クライアント用ダイアログプロシージャ
    */
    static BOOL CALLBACK ClientDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    /**
    * @brief サーバー用ダイアログプロシージャ
    */
    static BOOL CALLBACK ServerDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
public:
    static IWindowProc* addProcedure(DialogProcType type, IWindowProc* proc);
    static void removeProcedure(DialogProcType type, IWindowProc* procIt);
private:
    //static WindowProcContainer mClientDlgProc; //!< クライアント用プロシージャリスト
    //static WindowProcContainer mServerDlgProc; //!< サーバー用プロシージャリスト
    static std::unordered_map<DialogProcType, WindowProcContainer> mProceduresContainer;
};

} //Window 