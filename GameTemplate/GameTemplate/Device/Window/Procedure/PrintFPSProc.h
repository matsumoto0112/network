#pragma once
#include "Device/Window/Procedure/IWindowProc.h"
#include "Device/Window/Procedure/MenuCheckedController.h"
#include <functional>

namespace Window {

/**
* @class PrintFPSProc
* @brief FPS表示が選択されたときのプロシージャ
*/
class PrintFPSProc : public IWindowProc {
    using PrintFunc = std::function<void(void)>;
public:
    /**
    * @brief コンストラクタ
    * @param hWnd ウィンドウハンドル
    * @param func FPSを表示させるために呼ぶ関数
    */
    PrintFPSProc(HWND hWnd, PrintFunc func);
    /**
    * @brief デストラクタ
    */
    virtual ~PrintFPSProc();
    /**
    * @brief ウィンドウプロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
private:
    PrintFunc mFunc; //!< 表示させるための関数
    MenuCheckedController mMenuCheckedController; //!< メニューのチェック管理
};

} //Window 