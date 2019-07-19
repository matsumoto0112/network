#pragma once
#include <functional>
#include "Network/Socket.h"
#include "Utility/Thread/ThreadBase.h"
#include "Utility/Thread/MessageBuffer.h"
#include "Network/SocketException.h"
#include "Network/ServerSocket.h"

namespace Network {
class ServerSocket;
/**
* @class GameServerThread
* @brief ゲームのサーバー側スレッド
*/
class GameServerThread : public Thread::ThreadBase {
    using Event = std::function<void(void)>;
public:
    /**
    * @brief コンストラクタ
    */
    GameServerThread(unsigned int bufferSize, int port);
    /**
    * @brief デストラクタ
    */
    ~GameServerThread();
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

    int getPort() const { return mPort; }

    void connectClient(std::unique_ptr<Socket> socket);
    void setDisconnectEvent(Event disconnectEvent) { mDisconnectEvent = disconnectEvent; }

    std::list<std::string> getAllMessage();
private:
    std::unique_ptr<Socket> mTCPSocket; //!< TCPソケット
    Thread::MessageBuffer mMessageBuffer; //!< メッセージのバッファ
    ServerSocket mServerSocket;
    int mPort;
public:
    Event mDisconnectEvent;
    Event mConnectEvent;
};

template<>
inline void GameServerThread::sendMessage(const std::string& data) {
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
inline void GameServerThread::sendMessage(const T& data) {
    sendMessage(data.encode());
}


} //Network 