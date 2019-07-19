#pragma once
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class EndProc
* @brief メニューから終了が選ばれたときのプロシージャ
*/
class EndProc : public IWindowProc {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~EndProc();
    /**
    * @brief ウィンドウプロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
};

} //Window 