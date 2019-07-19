#pragma once

#include <stdexcept>

/**
* @class SocketException
* @brief ソケット例外クラス
*/
class SocketException : public std::runtime_error {
public:
    /**
    * コンストラクタ
    * @param msg メッセージ
    */
    SocketException(const std::string& msg)
        :std::runtime_error(msg) {}
};