#pragma once

#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class LeftButtonDownProc
* @brief discription
*/
class LeftButtonDownProc :public IWindowProc {
    using ClickFunc = std::function<void(void)>;
public:
    /**
    * @brief コンストラクタ
    */
    LeftButtonDownProc(ClickFunc left);
    /**
    * @brief デストラクタ
    */
    ~LeftButtonDownProc();
    // IWindowProc を介して継承されました
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
private:
    ClickFunc mLeftClick;
};

} //Window 