#pragma once

#include <memory>
#include <string>
#include "Network/InetSocketAddress.h"

namespace Network {
class SocketImpl;

/**
* @class Socket
* @brief ソケットクラス
*/
class Socket {
public:
    /**
    * コンストラクタ
    */
    Socket();
    /**
    * コンストラクタ
    * @param address ソケットアドレス
    */
    Socket(const InetSocketAddress& address);
    /**
    * コンストラクタ
    * @param address アドレス
    * @param port ポート番号
    */
    Socket(const InetAddress& address, int port);
    /**
    * コンストラクタ
    * @param host ホスト名
    * @param port ポート番号
    */
    Socket(const std::string& host, int port);
    /**
    * コンストラクタ
    * @param impl ソケット実装オブジェクト
    */
    Socket(SocketImpl* impl);
    /**
    * デストラクタ
    */
    virtual ~Socket();
    /**
    * ソケットの接続
    * @param address ソケットアドレス
    */
    void connect(const InetSocketAddress& address);
    /**
    * ソケットの接続
    * @param address アドレス
    * @param port ポート番号
    */
    void connect(const InetAddress& address, int port);
    /**
    * ソケットの接続
    * @param host ホスト名
    * @param port ポート番号
    */
    void connect(const std::string& host, int port);
    /**
    * ソケットを閉じる
    */
    void close();
    /**
    * 接続先のソケットにデータを送信
    * @param buffer バッファ
    * @param size バッファのサイズ
    */
    int send(const void* buffer, int size);
    /**
    * 接続先のソケットにデータを送信
    * @param msg 送信するメッセージ
    */
    int send(const std::string& msg);
    /**
    * 接続先のソケットからデータを受信
    * @param buffer バッファ
    * @param size バッファのサイズ
    */
    int recieve(void* buffer, int size);
    /**
    * 接続先のソケットからデータを受信
    * @return 受信したメッセージ
    */
    std::string recieve();
    /**
    * ソケットのアドレスを取得
    */
    InetAddress getAddress() const;
    /**
    * ポート番号を取得
    */
    int getPort() const;
    /**
    * ソケットのローカルアドレスを取得
    */
    InetAddress getLocalAddress() const;
    /**
    * ソケットのローカルポート番号を取得
    */
    int getLocalPort() const;
    /**
    * 接続中か調べる
    */
    bool isConnected() const;
    /**
    * シャットダウン
    */
    void shutDown(int how = Socket::SHUTDOWN_BOTH);
public:
    static const int SHUTDOWN_RECIEVE; //!< 受信をシャットダウン
    static const int SHUTDOWN_SEND; //!< 送信をシャットダウン
    static const int SHUTDOWN_BOTH; //!< 送受信をシャットダウン
private:
    //コピー禁止
    Socket(const Socket& other) = delete;
    //コピー禁止
    Socket& operator =(const Socket& other) = delete;
private:
    std::unique_ptr<SocketImpl> mImpl; //!< ソケット実装クラス
};

} //Network 