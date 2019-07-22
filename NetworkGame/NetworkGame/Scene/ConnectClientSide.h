#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include "Scene/ConnectSceneBase.h"

namespace Window {
class IWindowProc;
} //Window 

namespace Network {
class GameClientThread;
} //Network 

namespace Scene {

/**
* @class ConnectClientSide
* @brief クライアント側のサーバー接続シーン
*/
class ConnectClientSide : public ConnectSceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    ConnectClientSide();
    /**
    * @brief デストラクタ
    */
    ~ConnectClientSide();
    /**
    * @brief 終了時処理
    * @return 次のシーン
    */
    virtual std::unique_ptr<IScene> end() override;
private:
    /**
    * @brief 接続ボタンが押されたときのイベント
    * @param address サーバーアドレス
    * @param port ポート番号
    */
    void pushConnectButton(const std::string& address, int port);
private:
    std::unique_ptr<Network::GameClientThread> mClient; //!< クライアントスレッド
    Window::IWindowProc* mConnectEventProc;
    Window::IWindowProc* mConnectCancelEventProc;
};

} //Scene 