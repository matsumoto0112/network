#pragma once

#include <functional>

namespace Utility {

class Timer {
private:
    using Func = std::function<void(void)>;
public:
    Timer(float time, Func timerEvent);
    ~Timer();
    void update(float delta);
    void setTime(float time);
    bool isTime() const { return mTime <= 0.0f; }
    void init();
    void setEvent(Func timerEvent) { mTimerEvent = timerEvent; }
    float rate() const { return mTime / mMaxTime; }
    float time() const { return mTime; }
private:
    bool mIsActive;
    float mTime;
    float mMaxTime;
    Func mTimerEvent;
};

} //Utility 