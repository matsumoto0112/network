#pragma once

#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class InitProc
* @brief ダイアログ初期化時のプロシージャ
*/
class InitProc : public IWindowProc {
public:
    /**
    * @brief コンストラクタ
    */
    InitProc();
    /**
    * @brief デストラクタ
    */
    ~InitProc();
    /**
    * @brief プロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) override;
};
} //Window 