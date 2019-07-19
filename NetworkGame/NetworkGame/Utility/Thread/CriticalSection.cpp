#include "CriticalSection.h"

namespace Thread {

CriticalSection::CriticalSection() {
    ::InitializeCriticalSection(&mCriticalSection);
}

CriticalSection::~CriticalSection() {
    ::DeleteCriticalSection(&mCriticalSection);
}

void CriticalSection::enter() {
    ::EnterCriticalSection(&mCriticalSection);
}

void CriticalSection::leave() {
    ::LeaveCriticalSection(&mCriticalSection);
}

CriticalSection::Lock::Lock(CriticalSection& cs)
    :mCriticalSection(cs) {
    mCriticalSection.enter();
}

CriticalSection::Lock::~Lock() {
    mCriticalSection.leave();
}

} //Thread 
