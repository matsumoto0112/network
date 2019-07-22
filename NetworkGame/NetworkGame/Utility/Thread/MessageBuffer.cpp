#include "MessageBuffer.h"

namespace Thread {

MessageBuffer::MessageBuffer(unsigned int bufferSize)
    :mBufferSize(bufferSize) {}

MessageBuffer::~MessageBuffer() {}

void MessageBuffer::clear() {
    CriticalSection::Lock gurad(mBufferLock);
    mBuffer.clear();
}

void MessageBuffer::add(const std::string& message) {
    CriticalSection::Lock gurad(mBufferLock);
    mBuffer.emplace_back(message);
    while (mBuffer.size() > mBufferSize) {
        mBuffer.pop_front();
    }
}

std::string MessageBuffer::getMessage() {
    CriticalSection::Lock gurad(mBufferLock);

    std::string res = mBuffer.front();
    mBuffer.pop_front();
    return res;
}

std::list<std::string> MessageBuffer::getAllMessage() {
    CriticalSection::Lock gurad(mBufferLock);
    std::list<std::string> res(mBuffer.size());
    std::copy(mBuffer.begin(), mBuffer.end(), res.begin());
    mBuffer.clear();
    return res;
}

} //Thread 