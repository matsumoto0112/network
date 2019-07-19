#pragma once

#include <memory>
#include "Network/Socket.h"

namespace Network {

/**
* @class ServerSocket
* @brief �T�[�o�[�\�P�b�g�N���X
*/
class ServerSocket {
public:
    /**
    * �R���X�g���N�^
    */
    ServerSocket();
    /**
    * �R���X�g���N�^
    * �|�[�g�ԍ��Ńo�C���h����
    * @param port �{�[�g�ԍ�
    * @param backlog �o�b�N���O
    */
    ServerSocket(int port, int backlog = 0);
    /**
    * �f�X�g���N�^
    */
    virtual ~ServerSocket();
    /**
    * �ڑ��v����ҋ@���ă\�P�b�g���󂯓����
    * @return �󂯓��ꂽ�\�P�b�g
    */
    std::unique_ptr<Socket> accept();
    /**
    * �\�P�b�g���o�C���h���A���X����ԂɂȂ�
    */
    void bind(int port, int backlog = 0);
    /**
    * �\�P�b�g�����
    */
    void close();
    /**
    * �\�P�b�g�̃A�h���X���擾
    */
    InetAddress getAddress() const;
    /**
    * �\�P�b�g�̃|�[�g�ԍ����擾
    */
    int getPort() const;
private:
    //�R�s�[�֎~
    ServerSocket(const ServerSocket& other) = delete;
    //�R�s�[�֎~
    ServerSocket& operator =(const ServerSocket& other) = delete;
private:
    std::unique_ptr<SocketImpl> mImpl; //!< �\�P�b�g�����N���X
};

} //Network 
