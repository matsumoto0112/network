#include "Timer.h"

namespace Utility {

Timer::Timer(float time, Func timerEvent)
    :mIsActive(true), mTime(time), mMaxTime(time), mTimerEvent(timerEvent) {}

Timer::~Timer() {}

void Timer::update(float delta) {
    if (!mIsActive)return;

    mTime -= delta;

    if (mTime <= 0) {
        mIsActive = false;
        if (mTimerEvent != nullptr) {
            mTimerEvent();
        }
    }
}

void Timer::setTime(float time) {
    mTime = time;
    mMaxTime = time;
    mIsActive = true;
}

void Timer::init() {
    mTime = mMaxTime;
    mIsActive = true;
}

} //Utility 
