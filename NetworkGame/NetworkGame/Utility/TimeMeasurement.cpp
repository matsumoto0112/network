#include "TimeMeasurement.h"
#include <typeinfo>

Utility::TimeMeasurement::TimeMeasurement() {
    mGetTimeFuncs.emplace(UnitType::MilliSeconds, [](const auto& duration) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    });   
    mGetTimeFuncs.emplace(UnitType::MicroSeconds, [](const auto& duration) {
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    });
}

Utility::TimeMeasurement::~TimeMeasurement() {}

void Utility::TimeMeasurement::start() {
    mStartTime = std::chrono::system_clock::now();
}

long long Utility::TimeMeasurement::end(UnitType type) {
    Time end = std::chrono::system_clock::now();
    auto duration = end - mStartTime;
    return mGetTimeFuncs[type](duration);
}