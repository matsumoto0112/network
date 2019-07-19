#pragma once

#include <string>
#include <ostream>
#include <list>
#include "Utility/Thread/CriticalSection.h"

namespace Thread {

/**
* @class MessageBuffer
* @brief メッセージバッファクラス
*/
class MessageBuffer {
public:
    /**
    * @brief コンストラクタ
    * @param bufferSize メッセージの最大数
    */
    MessageBuffer(unsigned int bufferSize);
    /**
    * @brief デストラクタ
    */
    ~MessageBuffer();
    /**
    * @brief メッセージの消去
    */
    void clear();
    /**
    * @brief メッセージの追加
    * @param message 追加するメッセージ
    */
    void add(const std::string& message);
    /**
    * @brief 先頭のメッセージの取得
    */
    std::string getMessage();
    /**
    * @brief すべてのメッセージの取得
    * @details 受信した順番で並んでいる
    */
    std::list<std::string> getAllMessage();
private:
    using MessageContainer = std::list<std::string>;
    MessageContainer mBuffer; //!< メッセージバッファ
    MessageContainer::size_type mBufferSize; //!< メッセージの最大数
    CriticalSection mBufferLock; //!< バッファ用クリティカルセクション
};
} //Thread
