#pragma once

#include "Utility/Thread/IRunnable.h"

namespace Thread {

/**
* @class ThreadBase
* @brief スレッドクラス
*/
class ThreadBase : public IRunnable {
public:
    /**
    * @brief コンストラクタ
    */
    ThreadBase(IRunnable* runnable = nullptr);
    /**
    * @brief デストラクタ
    */
    virtual ~ThreadBase();
    /**
    * @brief スレッドの開始
    */
    virtual void start();
    /**
    * @brief スレッドの開始
    */
    virtual void start(IRunnable* runnable);
    /**
    * @brief スレッドの終了を待機する
    */
    void join();
    /**
    * @brief スレッドの実行
    */
    virtual void run() override;
    /**
    * @brief スリープする
    */
    static void sleep(unsigned int millsecond);
private:
    /**
    * @brief コールバック関数
    */
    static void callBack(void* runnable);
private:
    void* mHandle; //!< スレッドハンドル
    IRunnable* mRunnable; //!< 実行するスレッド
};

} //Thread 
