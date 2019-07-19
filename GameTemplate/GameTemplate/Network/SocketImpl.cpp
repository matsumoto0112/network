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
    //�V�����\�P�b�g���쐬
    SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        throw SocketException("�\�P�b�g���쐬�ł��܂���B");
    }

    //�T�[�o�[�ւ̃A�h���X���쐬
    SOCKADDR_IN serverAddress;
    std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(address.getPort());
    serverAddress.sin_addr.s_addr = address.getInetAddress().getAddress();

    //�T�[�o�[�Ɛڑ�����
    if (::connect(sock, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        ::closesocket(sock);
        throw SocketException("�ڑ��ł��܂���ł����B");
    }

    close();
    mSocketAddress = address;
    mSocket = sock;
}

void SocketImpl::close() {
    if (!isConnected())return;

    //�V���b�g�_�E������
    shutdown(SHUTDOWN_BOTH);
    //�\�P�b�g�����
    ::closesocket(mSocket);
    //�\�P�b�g�A�h���X��������
    mSocketAddress = InetSocketAddress();
    //�\�P�b�g�n���h����������
    mSocket = INVALID_SOCKET;
}

int SocketImpl::send(const void* buffer, int size) {
    int result = ::send(mSocket, (const char*)buffer, size, 0);

    if (!success(result)) {
        throw SocketException("���M�ł��܂���ł����B");
    }
    return result;
}

int SocketImpl::recieve(void* buffer, int size) {
    int result = ::recv(mSocket, (char*)buffer, size, 0);
    if (!success(result)) {
        throw SocketException("��M�ł��܂���ł����B");
    }
    return result;
}

SocketImpl* SocketImpl::accept() {
    std::unique_ptr<SocketImpl> client = std::make_unique<SocketImpl>();

    //�ڑ��̎󂯓���
    SOCKADDR_IN saddr;
    int len = (int)sizeof(saddr);
    SOCKET sock = ::accept(mSocket, (SOCKADDR*)&saddr, &len);
    if (sock == INVALID_SOCKET) {
        throw SocketException("�ڑ��̎󂯓���Ɏ��s���܂����B");
    }

    //�󂯓��ꂽ�ڑ��̃\�P�b�g�A�h���X��ݒ�
    std::string address = ::inet_ntoa(saddr.sin_addr);
    client->mSocketAddress = InetSocketAddress(InetAddress(address), saddr.sin_port);

    client->mSocket = sock;

    return client.release();
}

void SocketImpl::bind(int port) {
    //�V�����\�P�b�g���쐬����
    SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        throw SocketException("�\�P�b�g���쐬�ł��܂���B");
    }

    SOCKADDR_IN serverAddress;
    std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);

    //�o�C���h����
    if (::bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        ::closesocket(sock);
        throw SocketException("�o�C���h�Ɏ��s���܂����B");
    }

    //�\�P�b�g�̐ݒ�
    mSocketAddress = InetSocketAddress(InetAddress(INADDR_ANY), port);
    mSocket = sock;
}

void SocketImpl::listen(int backlog) {
    //�N���C�A���g����̐ڑ��҂��̏�Ԃɂ���
    if (::listen(mSocket, backlog) == SOCKET_ERROR) {
        throw SocketException("�ڑ��҂��̎��s");
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
