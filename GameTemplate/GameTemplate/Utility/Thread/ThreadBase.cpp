#include "ThreadBase.h"
#include <Windows.h>
#include <process.h>

namespace Thread {

ThreadBase::ThreadBase(IRunnable* runnable)
    :mHandle(nullptr), mRunnable(runnable) {
    if (!mRunnable)mRunnable = this;
}

ThreadBase::~ThreadBase() {}

void ThreadBase::start() {
    mHandle = reinterpret_cast<void*>(::_beginthread(callBack, 0, this));
}

void ThreadBase::start(IRunnable* runnable) {
    mRunnable = runnable;
    start();
}

void ThreadBase::join() {
    if (mHandle) {
        ::WaitForSingleObject(mHandle, INFINITE);
    }
}

void ThreadBase::run() {}

void ThreadBase::sleep(unsigned int millsecond) {
    ::Sleep(millsecond);
}

void ThreadBase::callBack(void* runnable) {
    ThreadBase* thread = reinterpret_cast<ThreadBase*>(runnable);
    thread->mRunnable->run();
    thread->mHandle = nullptr;
}

} //Thread 