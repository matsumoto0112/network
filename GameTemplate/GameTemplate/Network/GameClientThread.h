#pragma once

#include <functional>
#include <memory>
#include "Network/Socket.h"
#include "Utility/Thread/ThreadBase.h"
#include "Utility/Thread/MessageBuffer.h"
#include "Network/SocketException.h"

namespace Network {

/**
* @class GameClientThread
* @brief �Q�[���̃N���C�A���g���X���b�h
*/
class GameClientThread : public Thread::ThreadBase {
    using Event = std::function<void(void)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param bufferSize �f�[�^��ۑ����Ă�����
    */
    GameClientThread(unsigned int bufferSize);
    /**
    * @brief �f�X�g���N�^
    */
    ~GameClientThread();
    /**
    * @brief �T�[�o�[�̃\�P�b�g�A�h���X�̐ݒ�
    * @param address �ݒ肷��\�P�b�g�A�h���X
    */
    void setServerAddress(const InetSocketAddress& address);
    /**
    * @brief �X���b�h�̎��s
    */
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
    std::list<std::string> getAllMessage();
    void setDisconnectEvent(Event disconnectEvent) { mDisconnectEvent = disconnectEvent; }
private:
    InetSocketAddress mServerAddress; //!< �T�[�o�[�̃\�P�b�g�A�h���X
    std::unique_ptr<Socket> mTCPSocket; //!< TCP�\�P�b�g
    Thread::MessageBuffer mMessageBuffer; //!< ���b�Z�[�W�̃o�b�t�@
public:
    Event mDisconnectEvent;
    Event mConnectEvent;
};

template<>
inline void GameClientThread::sendMessage(const std::string& data) {
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
inline void GameClientThread::sendMessage(const T& data) {
    sendMessage(data.encode());
}

} //Network 