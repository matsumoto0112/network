#pragma once

#include <string>
#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class ServerConnectProc
* @brief サーバー側で接続ボタンが押されたときのプロシージャ
*/
class ServerConnectProc :public IWindowProc {
    using ConnectFunc = std::function<void(int)>;
public:
    /**
    * @brief コンストラクタ
    * @param connectFunc 接続ボタンが押されたときのイベント
    */
    ServerConnectProc(ConnectFunc connectFunc);
    /**
    * @brief デストラクタ
    */
    ~ServerConnectProc();
    /**
    * @brief プロシージャ
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) override;
private:
    ConnectFunc mFunc; //!< 接続ボタンが押されたときのイベント関数
};
} //Window 