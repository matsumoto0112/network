#pragma once
#include <functional>
#include "Network/Socket.h"
#include "Utility/Thread/ThreadBase.h"
#include "Utility/Thread/MessageBuffer.h"
#include "Network/SocketException.h"
#include "Network/ServerSocket.h"

namespace Network {
class ServerSocket;
/**
* @class GameServerThread
* @brief �Q�[���̃T�[�o�[���X���b�h
*/
class GameServerThread : public Thread::ThreadBase {
    using Event = std::function<void(void)>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    GameServerThread(unsigned int bufferSize, int port);
    /**
    * @brief �f�X�g���N�^
    */
    ~GameServerThread();
    void run() override;

    /**
    * @brief �f�[�^�𑗐M����
    * @param data ���M����f�[�^
    */
    template <class T>
    void sendMessage(const T& data);
    /**
    * @brief �ڑ������H
    */
    bool isConnect() const;
    /**
    * @brief �����I������
    */
    void end();

    int getPort() const { return mPort; }

    void connectClient(std::unique_ptr<Socket> socket);
    void setDisconnectEvent(Event disconnectEvent) { mDisconnectEvent = disconnectEvent; }

    std::list<std::string> getAllMessage();
private:
    std::unique_ptr<Socket> mTCPSocket; //!< TCP�\�P�b�g
    Thread::MessageBuffer mMessageBuffer; //!< ���b�Z�[�W�̃o�b�t�@
    ServerSocket mServerSocket;
    int mPort;
public:
    Event mDisconnectEvent;
    Event mConnectEvent;
};

template<>
inline void GameServerThread::sendMessage(const std::string& data) {
    //�ڑ����Ă��Ȃ���Α��M���Ȃ�
    if (!isConnect())return;
    try {
            mTCPSocket->send(data);
    }
    catch (const SocketException& e) {
        mMessageBuffer.add(e.what());
    }
}

template<class T>
inline void GameServerThread::sendMessage(const T& data) {
    sendMessage(data.encode());
}


} //Network 