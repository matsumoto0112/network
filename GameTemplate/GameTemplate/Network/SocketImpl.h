#pragma once

#include <WinSock2.h>
#include "Network/InetSocketAddress.h"

namespace Network {

/**
* @class SocketImpl
* @brief �\�P�b�g�����N���X
*/
class SocketImpl {
public:
    /**
    * �R���X�g���N�^
    */
    SocketImpl();
    /**
    * �f�X�g���N�^
    */
    virtual ~SocketImpl();
    /**
    * �\�P�b�g�̐ڑ�
    * @param address �ڑ�����\�P�b�g
    */
    void connect(const InetSocketAddress& address);
    /**
    * �\�P�b�g�����
    */
    void close();
    /**
    * �ڑ���̃\�P�b�g�Ƀf�[�^�𑗐M
    * @param buffer ���M����f�[�^
    * @param size �f�[�^�̑傫��
    */
    int send(const void* buffer, int size);
    /**
    * �ڑ���̃\�P�b�g����f�[�^����M
    * @param buffer ��M����f�[�^
    * @param size �f�[�^�̑傫��
    */
    int recieve(void* buffer, int size);
    /**
    * �ڑ����󂯓����
    */
    SocketImpl* accept();
    /**
    * �w�肳�ꂽ�|�[�g�ԍ��Ƀ\�P�b�g���o�C���h����
    * @param port �|�[�g�ԍ�
    */
    void bind(int port);
    /**
    * �\�P�b�g�����X����Ԃɂ���
    */
    void listen(int backlog = 0);
    /**
    * �V���b�g�_�E�����s��
    */
    void shutdown(int how);
    /**
    * �ڑ���̃\�P�b�g�̃\�P�b�g�A�h���X���擾
    */
    InetSocketAddress getInetSocketAddress() const { return mSocketAddress; }
    /**
    * ���[�J���\�P�b�g�A�h���X���擾
    */
    InetSocketAddress getLocalInetSocketAddress() const;
    /**
    * �ڑ��������ׂ�
    */
    bool isConnected() const;
private:
    //�R�s�[�֎~
    SocketImpl& operator =(SocketImpl) = delete;
    //�R�s�[�֎~
    SocketImpl(const SocketImpl& other) = delete;
private:
    SOCKET mSocket; //!< �\�P�b�g�n���h��
    InetSocketAddress mSocketAddress; //!< �\�P�b�g�A�h���X
public:
    static const int SHUTDOWN_BOTH; //!< ����M���V���b�g�_�E��
    static const int SHUTDOWN_RECIEVE; //!< ��M���V���b�g�_�E��
    static const int SHUTDOWN_SEND; //!< ���M���V���b�g�_�E��
};

} //Network 
