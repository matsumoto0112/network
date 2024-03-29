#pragma once
#include <Windows.h>
#include <vector>
#include <memory>
#include "Resources/resource.h"
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class WindowProcedures
* @brief ウィンドウプロシージャ関数の定義
*/
class WindowProcedures {
public:
    /**
    * vメインウィンドウのウィンドウプロシージャ
    * @param hWnd メッセージの発生したウィンドウハンドル
    * @param message メッセージの種類
    * @param wParam パラメータ1
    * @param lParam パラメータ2
    * @return LRESULT 終了コード
    */
    static LRESULT CALLBACK mainWndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);

    /**
    * @brief サブウィンドウのウィンドウプロシージャ
    * @param hWnd メッセージの発生したウィンドウハンドル
    * @param message メッセージの種類
    * @param wParam パラメータ1
    * @param lParam パラメータ2
    * @return LRESULT 終了コード
    */
    static LRESULT CALLBACK subWndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);
public:
    static std::vector<std::unique_ptr<IWindowProc>> mWindowProcs; //!< ウィンドウプロシージャリスト
};

} //Window 
