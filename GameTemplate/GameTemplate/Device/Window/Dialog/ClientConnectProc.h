#pragma once

#include <string>
#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class ClientConnectProc
* @brief クライアント側で接続ボタンが押されたときのプロシージャ
*/
class ClientConnectProc :public IWindowProc {
    using ConnectFunc = std::function<void(const std::string& ,int)>;
public:
    /**
    * @brief コンストラクタ
    * @param connectFunc ボタンが押されたときのイベント
    */
    ClientConnectProc(ConnectFunc connectFunc);
    /**
    * @brief デストラクタ
    */
    ~ClientConnectProc();
    /**
    * @brief プロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) override;
private:
    ConnectFunc mFunc; //!< ボタンが押されたときのイベント関数
};
} //Window 