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
        //クライアントの接続を待機する
        mServerSocket.bind(mPort);

        std::cout << "クライアント接続待ち\n";
        mTCPSocket = mServerSocket.accept();
        std::cout << mTCPSocket->getAddress().getHostAddress() << "が接続しました\n";
        if (mConnectEvent) mConnectEvent();
        //メッセージを処理する
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
