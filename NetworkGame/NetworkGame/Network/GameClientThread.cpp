#include "GameClientThread.h"
#include <iostream>
#include "Network/SocketException.h"

namespace Network {

GameClientThread::GameClientThread(unsigned int bufferSize)
    :mMessageBuffer(bufferSize) {}

GameClientThread::~GameClientThread() {
    end();
}

void GameClientThread::setServerAddress(const InetSocketAddress& address) {
    mServerAddress = address;
}

void GameClientThread::run() {
    mMessageBuffer.clear();
    std::cout << "�ڑ����Ă��܂�...\n";

    try {
        mTCPSocket = std::make_unique<Socket>(mServerAddress);
        std::cout << "�ڑ��ɐ������܂���\n";
        std::string testMessage = "���M�e�X�g";
        if (mConnectEvent)mConnectEvent();
        while (isConnect()) {
            std::string mes = mTCPSocket->recieve();
            mMessageBuffer.add(mes);
            Thread::ThreadBase::sleep(0);
        }
    }
    catch (const SocketException& e) {
        std::cout << e.what() << "\n";
    }

    if (mTCPSocket) {
        mTCPSocket->close();
    }
    if (mDisconnectEvent) mDisconnectEvent();
    std::cout << "�ؒf���܂���\n";
}

bool GameClientThread::isConnect() const {
    return mTCPSocket->isConnected();
}

void GameClientThread::end() {
    if (mTCPSocket) {
        mTCPSocket->close();
    }
    join();
}

std::list<std::string> GameClientThread::getAllMessage() {
    return mMessageBuffer.getAllMessage();
}

} //Network 
