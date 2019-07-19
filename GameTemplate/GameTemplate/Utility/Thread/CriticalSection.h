#pragma once

#include <Windows.h>

namespace Thread {

/**
* @class CriticalSection
* @brief クリティカルセクションクラス
*/
class CriticalSection {
public:
    /**
    * @brief コンストラクタ
    */
    CriticalSection();
    /**
    * @brief デストラクタ
    */
    ~CriticalSection();
    /**
    * @brief クリティカルセクション開始
    */
    void enter();
    /**
    * @brief クリティカルセクション終了
    */
    void leave();

    /**
    * @class Lock
    * @brief ロッククラス
    */
    class Lock {
    public:
        /**
        * @brief コンストラクタ
        */
        Lock(CriticalSection& cs);
        /**
        * @brief デストラクタ
        */
        ~Lock();
    private:
        CriticalSection& mCriticalSection; //!< クリティカルセクション
    };
private:
    CRITICAL_SECTION mCriticalSection; //!< クリティカルセクション
};
} //Thread 
