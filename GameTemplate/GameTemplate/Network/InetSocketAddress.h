#pragma once

#include "Network/InetAddress.h"

namespace Network {

/**
* @class InetSocketAddress
* @brief インターネットソケットアドレス管理クラス
*/
class InetSocketAddress {
public:
    /**
    * コンストラクタ
    * @param address インターネットアドレス
    * @param port ポート番号
    */
    InetSocketAddress(const InetAddress& address = InetAddress(), int port = 0);
    /**
    * デストラクタ
    */
    virtual ~InetSocketAddress();
    /**
    * インターネットアドレスの取得
    */
    const InetAddress& getInetAddress() const { return mAddress; }
    /**
    * ポート番号の取得
    */
    int getPort() const { return mPort; }
private:
    InetAddress mAddress; //!< インターネットアドレス
    int mPort; //!< ポート番号
};
} //Network 