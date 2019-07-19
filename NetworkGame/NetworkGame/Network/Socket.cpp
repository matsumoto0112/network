#include "Socket.h"
#include "Network/SocketImpl.h"
#include <vector>

namespace Network {
const int Socket::SHUTDOWN_RECIEVE = SocketImpl::SHUTDOWN_RECIEVE;
const int Socket::SHUTDOWN_SEND = SocketImpl::SHUTDOWN_SEND;
const int Socket::SHUTDOWN_BOTH = SocketImpl::SHUTDOWN_BOTH;

Socket::Socket()
    :mImpl(std::make_unique<SocketImpl>()) {}

Socket::Socket(const InetSocketAddress& address)
    : Socket() {
    connect(address);
}

Socket::Socket(const InetAddress& address, int port)
    : Socket() {
    connect(address, port);
}

Socket::Socket(const std::string& host, int port)
    : Socket() {
    connect(host, port);
}

Socket::Socket(SocketImpl* impl)
    : mImpl(impl) {}

Socket::~Socket() {}

void Socket::connect(const InetSocketAddress& address) {
    mImpl->connect(address);
}

void Socket::connect(const InetAddress& address, int port) {
    connect(InetSocketAddress(address, port));
}

void Socket::connect(const std::string& host, int port) {
    connect(InetAddress(host), port);
}

void Socket::close() {
    if (mImpl->isConnected()) {
        mImpl->close();
    }
}

int Socket::send(const void* buffer, int size) {
    int total = 0;
    while (total < size) {
        total += mImpl->send(reinterpret_cast<const char*>(buffer) + total, size - total);
    }
    return total;
}

int Socket::send(const std::string& msg) {
    return send(msg.c_str(), (int)msg.size() + 1);
}

int Socket::recieve(void* buffer, int size) {
    int total = 0;
    while (total < size) {
        total += mImpl->recieve(reinterpret_cast<char*>(buffer) + total, size - total);
    }
    return total;
}

std::string Socket::recieve() {
    //受信バッファ
    std::vector<char> buffer;

    //ヌル文字まで受け取る
    char revchar;
    do {
        revchar = '\0';
        recieve(&revchar, sizeof(revchar));
        buffer.emplace_back(revchar);
    } while (revchar != '\0');

    return std::string(&buffer[0]);
}

InetAddress Socket::getAddress() const {
    return mImpl->getInetSocketAddress().getInetAddress();
}

int Socket::getPort() const {
    return mImpl->getInetSocketAddress().getPort();
}

InetAddress Socket::getLocalAddress() const {
    return mImpl->getLocalInetSocketAddress().getInetAddress();
}

int Socket::getLocalPort() const {
    return mImpl->getLocalInetSocketAddress().getPort();
}

bool Socket::isConnected() const {
    return mImpl->isConnected();
}

void Socket::shutDown(int how) {
    mImpl->shutdown(how);
}

} //Network 