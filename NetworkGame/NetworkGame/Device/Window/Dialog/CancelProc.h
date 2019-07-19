#pragma once

#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class CancelProc
* @brief ダイアログでキャンセルが押されたときのプロシージャ
*/
class CancelProc : public IWindowProc {
    using CancelFunc = std::function<void(void)>;
public:
    /**
    * @brief コンストラクタ
    * @param cancelFunc キャンセルが押されたときのイベント
    */
    CancelProc(CancelFunc cancelFunc);
    /**
    * @brief デストラクタ
    */
    ~CancelProc();
    /**
    * @brief プロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) override;
private:
    CancelFunc mFunc; //!< キャンセルが押されたときのイベント関数
};
} //Window 