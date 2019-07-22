#pragma once
#include <Windows.h>

namespace Window {
class Window;

/**
* @class DialogWindow
* @brief ダイアログウィンドウクラス
*/
class DialogWindow {
public:
    /**
    * @brief コンストラクタ
    * @param mainWindow メインウィンドウハンドル
    * @param dialogID 作成するダイアログID
    * @param dlgProc ダイアログを処理するプロシージャ
    */
    DialogWindow(Window* parentWindow, UINT dialogID, DLGPROC dlgProc);
    /**
    * @brief デストラクタ
    */
    ~DialogWindow();
    /**
    * @brief ダイアログを閉じる
    */
    void close();
    /**
    * @brief ハンドルの取得
    */
    HWND getHandle() const { return mDlgHandle; }
    bool isEnd() const { return mIsEnd; }
private:
    HWND mDlgHandle; //!< ダイアログハンドル
    bool mIsEnd;
};

} //Window 