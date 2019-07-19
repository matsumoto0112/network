#include "SocketImpl.h"
#include "Network/SocketException.h"
#include <memory>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning (disable: 4996)

namespace {
bool success(int result) {
    return !(result == SOCKET_ERROR || result == 0);
}
}

namespace Network {
const int SocketImpl::SHUTDOWN_RECIEVE = SD_RECEIVE;
const int SocketImpl::SHUTDOWN_SEND = SD_SEND;
const int SocketImpl::SHUTDOWN_BOTH = SD_BOTH;

SocketImpl::SocketImpl()
    :mSocket(INVALID_SOCKET) {}

SocketImpl::~SocketImpl() {
    close();
}

void SocketImpl::connect(const InetSocketAddress& address) {
    //新しいソケットを作成
    SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        throw SocketException("ソケットが作成できません。");
    }

    //サーバーへのアドレスを作成
    SOCKADDR_IN serverAddress;
    std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(address.getPort());
    serverAddress.sin_addr.s_addr = address.getInetAddress().getAddress();

    //サーバーと接続する
    if (::connect(sock, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        ::closesocket(sock);
        throw SocketException("接続できませんでした。");
    }

    close();
    mSocketAddress = address;
    mSocket = sock;
}

void SocketImpl::close() {
    if (!isConnected())return;

    //シャットダウン処理
    shutdown(SHUTDOWN_BOTH);
    //ソケットを閉じる
    ::closesocket(mSocket);
    //ソケットアドレスを初期化
    mSocketAddress = InetSocketAddress();
    //ソケットハンドラを初期化
    mSocket = INVALID_SOCKET;
}

int SocketImpl::send(const void* buffer, int size) {
    int result = ::send(mSocket, (const char*)buffer, size, 0);

    if (!success(result)) {
        throw SocketException("送信できませんでした。");
    }
    return result;
}

int SocketImpl::recieve(void* buffer, int size) {
    int result = ::recv(mSocket, (char*)buffer, size, 0);
    if (!success(result)) {
        throw SocketException("受信できませんでした。");
    }
    return result;
}

SocketImpl* SocketImpl::accept() {
    std::unique_ptr<SocketImpl> client = std::make_unique<SocketImpl>();

    //接続の受け入れ
    SOCKADDR_IN saddr;
    int len = (int)sizeof(saddr);
    SOCKET sock = ::accept(mSocket, (SOCKADDR*)&saddr, &len);
    if (sock == INVALID_SOCKET) {
        throw SocketException("接続の受け入れに失敗しました。");
    }

    //受け入れた接続のソケットアドレスを設定
    std::string address = ::inet_ntoa(saddr.sin_addr);
    client->mSocketAddress = InetSocketAddress(InetAddress(address), saddr.sin_port);

    client->mSocket = sock;

    return client.release();
}

void SocketImpl::bind(int port) {
    //新しいソケットを作成する
    SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        throw SocketException("ソケットが作成できません。");
    }

    SOCKADDR_IN serverAddress;
    std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);

    //バインドする
    if (::bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        ::closesocket(sock);
        throw SocketException("バインドに失敗しました。");
    }

    //ソケットの設定
    mSocketAddress = InetSocketAddress(InetAddress(INADDR_ANY), port);
    mSocket = sock;
}

void SocketImpl::listen(int backlog) {
    //クライアントからの接続待ちの状態にする
    if (::listen(mSocket, backlog) == SOCKET_ERROR) {
        throw SocketException("接続待ちの失敗");
    }
}

void SocketImpl::shutdown(int how) {
    ::shutdown(mSocket, how);
}

InetSocketAddress SocketImpl::getLocalInetSocketAddress() const {
    SOCKADDR_IN saddr;
    int len = (int)sizeof(saddr);
    if (::getsockname(mSocket, (struct sockaddr*)&saddr, &len) == SOCKET_ERROR) {
        return InetSocketAddress(InetAddress());
    }
    return InetSocketAddress(saddr.sin_addr.s_addr, saddr.sin_port);
}

bool SocketImpl::isConnected() const {
    return mSocket != INVALID_SOCKET;
}

} //Network 
