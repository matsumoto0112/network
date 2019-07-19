#include "GameServerThread.h"
#include <iostream>
#include "Network/ServerSocket.h"

namespace Network {

GameServerThread::GameServerThread(unsigned int bufferSize, int port)
    :mMessageBuffer(bufferSize), mPort(port) {}

GameServerThread::~GameServerThread() {
    end();
}

void GameServerThread::run() {
    try {
        //�N���C�A���g�̐ڑ���ҋ@����
        mServerSocket.bind(mPort);

        std::cout << "�N���C�A���g�ڑ��҂�\n";
        mTCPSocket = mServerSocket.accept();
        std::cout << mTCPSocket->getAddress().getHostAddress() << "���ڑ����܂���\n";
        if (mConnectEvent) mConnectEvent();
        //���b�Z�[�W����������
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
}

bool GameServerThread::isConnect() const {
    return mTCPSocket->isConnected();
}

void GameServerThread::end() {
    mServerSocket.close();
    if (mTCPSocket) {
        mTCPSocket->close();
    }
    join();
}

void GameServerThread::connectClient(std::unique_ptr<Socket> socket) {
    mTCPSocket = std::move(socket);
}

std::list<std::string> GameServerThread::getAllMessage() {
    return mMessageBuffer.getAllMessage();
}

} //Network 
