#pragma once

#include <Windows.h>
#include "Scene/ConnectSceneBase.h"

namespace Window {
class IWindowProc;
} //Window 

namespace Network {
class GameServerThread;
} //Network 

namespace Scene {

/**
* @class ConnectServerSide
* @brief サーバー側のクライアント接続シーン
*/
class ConnectServerSide :public ConnectSceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    ConnectServerSide();
    /**
    * @brief デストラクタ
    */
    ~ConnectServerSide();
    /**
    * @brief 終了時処理
    * @return 次のシーン
    */
    virtual std::unique_ptr<IScene> end() override;
private:
    /**
    * @brief 接続ボタンが押されたときのイベント
    * @param port ポート番号
    */
    void puchConnectButton(int port);
private:
    std::unique_ptr<Network::GameServerThread> mServerThread; //!< サーバースレッド
    Window::IWindowProc* mConnectEventProc;
    Window::IWindowProc* mConnectCancelEventProc;
};

} //Scene 