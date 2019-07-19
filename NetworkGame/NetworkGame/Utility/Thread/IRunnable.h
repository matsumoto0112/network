#pragma once

namespace Thread {
/**
* @class IRunnable
* @brief スレッド実行インターフェース
*/
class IRunnable {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IRunnable() = default;
    /**
    * @brief 実行
    */
    virtual void run() = 0;
};

} //Thread 