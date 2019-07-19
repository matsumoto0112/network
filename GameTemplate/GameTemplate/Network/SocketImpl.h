#pragma once

#include <WinSock2.h>
#include "Network/InetSocketAddress.h"

namespace Network {

/**
* @class SocketImpl
* @brief ソケット実装クラス
*/
class SocketImpl {
public:
    /**
    * コンストラクタ
    */
    SocketImpl();
    /**
    * デストラクタ
    */
    virtual ~SocketImpl();
    /**
    * ソケットの接続
    * @param address 接続するソケット
    */
    void connect(const InetSocketAddress& address);
    /**
    * ソケットを閉じる
    */
    void close();
    /**
    * 接続先のソケットにデータを送信
    * @param buffer 送信するデータ
    * @param size データの大きさ
    */
    int send(const void* buffer, int size);
    /**
    * 接続先のソケットからデータを受信
    * @param buffer 受信するデータ
    * @param size データの大きさ
    */
    int recieve(void* buffer, int size);
    /**
    * 接続を受け入れる
    */
    SocketImpl* accept();
    /**
    * 指定されたポート番号にソケットをバインドする
    * @param port ポート番号
    */
    void bind(int port);
    /**
    * ソケットをリスン状態にする
    */
    void listen(int backlog = 0);
    /**
    * シャットダウンを行う
    */
    void shutdown(int how);
    /**
    * 接続先のソケットのソケットアドレスを取得
    */
    InetSocketAddress getInetSocketAddress() const { return mSocketAddress; }
    /**
    * ローカルソケットアドレスを取得
    */
    InetSocketAddress getLocalInetSocketAddress() const;
    /**
    * 接続中か調べる
    */
    bool isConnected() const;
private:
    //コピー禁止
    SocketImpl& operator =(SocketImpl) = delete;
    //コピー禁止
    SocketImpl(const SocketImpl& other) = delete;
private:
    SOCKET mSocket; //!< ソケットハンドラ
    InetSocketAddress mSocketAddress; //!< ソケットアドレス
public:
    static const int SHUTDOWN_BOTH; //!< 送受信をシャットダウン
    static const int SHUTDOWN_RECIEVE; //!< 受信をシャットダウン
    static const int SHUTDOWN_SEND; //!< 送信をシャットダウン
};

} //Network 
