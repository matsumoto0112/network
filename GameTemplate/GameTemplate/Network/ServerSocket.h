#pragma once

#include <memory>
#include "Network/Socket.h"

namespace Network {

/**
* @class ServerSocket
* @brief サーバーソケットクラス
*/
class ServerSocket {
public:
    /**
    * コンストラクタ
    */
    ServerSocket();
    /**
    * コンストラクタ
    * ポート番号でバインドする
    * @param port ボート番号
    * @param backlog バックログ
    */
    ServerSocket(int port, int backlog = 0);
    /**
    * デストラクタ
    */
    virtual ~ServerSocket();
    /**
    * 接続要求を待機してソケットを受け入れる
    * @return 受け入れたソケット
    */
    std::unique_ptr<Socket> accept();
    /**
    * ソケットをバインドし、リスン状態になる
    */
    void bind(int port, int backlog = 0);
    /**
    * ソケットを閉じる
    */
    void close();
    /**
    * ソケットのアドレスを取得
    */
    InetAddress getAddress() const;
    /**
    * ソケットのポート番号を取得
    */
    int getPort() const;
private:
    //コピー禁止
    ServerSocket(const ServerSocket& other) = delete;
    //コピー禁止
    ServerSocket& operator =(const ServerSocket& other) = delete;
private:
    std::unique_ptr<SocketImpl> mImpl; //!< ソケット実装クラス
};

} //Network 
