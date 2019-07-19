#pragma once

#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"
#include "Device/Window/Procedure/MenuCheckedController.h"

namespace Window {

/**
* @class ShowCursorProc
* @brief カーソルの表示が選択されたときのプロシージャ
*/
class ShowCursorProc :public IWindowProc {
    using CursorEvent = std::function<void()>;
    using CursorToggleEvent = std::function<void(bool)>;
public:
    /**
    * @brief コンストラクタ
    * @param hWnd ウィンドウハンドル
    * @param showEvent カーソル表示時のイベント
    * @param hideEvent カーソル非表示時のイベント
    */
    ShowCursorProc(HWND hWnd, CursorEvent showEvent, CursorEvent hideEvent);
    /**
    * @brief デストラクタ
    */
    virtual ~ShowCursorProc();
    /**
    * @brief ウィンドウプロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
private:
    MenuCheckedController mMenuCheckedController; //!< メニューのチェック管理
    CursorToggleEvent mEvent; //!< カーソルの表示非表示イベント
};
} //Window 
