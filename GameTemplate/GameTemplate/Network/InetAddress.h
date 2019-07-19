#pragma once

#include <string>

namespace Network {

/**
* @class InetAddress
* @brief IPアドレスを管理する
*/
class InetAddress {
public:
    /**
    * コンストラクタ
    * @param address IPアドレス
    */
    InetAddress(unsigned long address = InetAddress::NONE);
    /**
    * コンストラクタ
    * @param address ホストアドレス
    */
    InetAddress(const std::string& address);
    /**
    * デストラクタ
    */
    virtual ~InetAddress();
    /**
    * IPアドレスの取得
    */
    unsigned long getAddress() const { return mIPAddress; }
    /**
    * ホストアドレスの取得
    */
    std::string getHostAddress() const;
public:
    /**
    * 代入演算子オーバーロード
    */
    InetAddress& operator =(const InetAddress& other);
    /**
    * 代入演算子オーバーロード
    */
    InetAddress& operator =(const std::string& host);
private:
    unsigned long mIPAddress; //!< IPアドレス
    static const unsigned long NONE; //!< 無効なIPアドレス
};
} //Network 
