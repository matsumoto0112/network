#pragma once

#include <functional>
#include <memory>
#include "Network/Socket.h"
#include "Utility/Thread/ThreadBase.h"
#include "Utility/Thread/MessageBuffer.h"
#include "Network/SocketException.h"

namespace Network {

/**
* @class GameClientThread
* @brief ゲームのクライアント側スレッド
*/
class GameClientThread : public Thread::ThreadBase {
    using Event = std::function<void(void)>;
public:
    /**
    * @brief コンストラクタ
    * @param bufferSize データを保存しておく量
    */
    GameClientThread(unsigned int bufferSize);
    /**
    * @brief デストラクタ
    */
    ~GameClientThread();
    /**
    * @brief サーバーのソケットアドレスの設定
    * @param address 設定するソケットアドレス
    */
    void setServerAddress(const InetSocketAddress& address);
    /**
    * @brief スレッドの実行
    */
    void run() override;

    /**
    * @brief データを送信する
    * @param data 送信するデータ
    */
    template <class T>
    void sendMessage(const T& data);
    /**
    * @brief 接続中か？
    */
    bool isConnect() const;
    /**
    * @brief 強制終了処理
    */
    void end();
    std::list<std::string> getAllMessage();
    void setDisconnectEvent(Event disconnectEvent) { mDisconnectEvent = disconnectEvent; }
private:
    InetSocketAddress mServerAddress; //!< サーバーのソケットアドレス
    std::unique_ptr<Socket> mTCPSocket; //!< TCPソケット
    Thread::MessageBuffer mMessageBuffer; //!< メッセージのバッファ
public:
    Event mDisconnectEvent;
    Event mConnectEvent;
};

template<>
inline void GameClientThread::sendMessage(const std::string& data) {
    //接続していなければ送信しない
    if (!isConnect())return;
    try {
        mTCPSocket->send(data);
    }
    catch (const SocketException& e) {
        mMessageBuffer.add(e.what());
    }
}

template<class T>
inline void GameClientThread::sendMessage(const T& data) {
    sendMessage(data.encode());
}

} //Network 