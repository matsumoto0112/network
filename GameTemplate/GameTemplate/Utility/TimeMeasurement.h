#pragma once

#include <chrono>
#include <unordered_map>
#include <Windows.h>
#include <functional>
#include "Utility/Singleton.h"

namespace Utility {

/**
* @class TimeMeasurement
* @brief 時間計測
*/
class TimeMeasurement : public Singleton<TimeMeasurement> {
    /**
    * @enum UnitType
    * @brief 時間の単位
    */
    enum class UnitType {
        MilliSeconds,
        MicroSeconds,
    };

private:
    using Time = std::chrono::system_clock::time_point;
    //引数に計測時間間隔、戻り値にその間隔に変換した時間を返す関数
    using GetTimeFunc = std::function<
        long long(std::chrono::duration<long long, std::ratio_multiply<std::hecto, std::nano>>)
    >;
public:
    /**
    * @brief コンストラクタ
    */
    TimeMeasurement();
    /**
    * @brief デストラクタ
    */
    ~TimeMeasurement();
    /**
    * @brief 計測開始
    */
    void start();
    /**
    * @brief 計測終了
    * @param 計測した時間の単位
    * @return startからendまでの経過時間
    */
    long long end(UnitType type = UnitType::MilliSeconds);
private:
    Time mStartTime; //!< 開始時間
    std::unordered_map<UnitType, GetTimeFunc> mGetTimeFuncs;
};

} //Utility 