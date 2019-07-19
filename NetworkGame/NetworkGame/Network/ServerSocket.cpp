#include "ServerSocket.h"
#include "Network/SocketImpl.h"

namespace Network {

ServerSocket::ServerSocket()
    :mImpl(std::make_unique<SocketImpl>()) {}

ServerSocket::ServerSocket(int port, int backlog)
    : ServerSocket() {
    bind(port, backlog);
}

ServerSocket::~ServerSocket() {}

std::unique_ptr<Socket> ServerSocket::accept() {
    return std::make_unique<Socket>(mImpl->accept());
}

void ServerSocket::bind(int port, int backlog) {
    mImpl->bind(port);
    mImpl->listen(backlog);
}

void ServerSocket::close() {
    if (mImpl->isConnected()) {
        mImpl->close();
    }
}

InetAddress ServerSocket::getAddress() const {
    return mImpl->getLocalInetSocketAddress().getInetAddress();
}

int ServerSocket::getPort() const {
    return mImpl->getLocalInetSocketAddress().getPort();
}

} //Network 
