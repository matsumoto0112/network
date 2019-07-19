#pragma once

#include <memory>
#include <string>
#include "Network/InetSocketAddress.h"

namespace Network {
class SocketImpl;

/**
* @class Socket
* @brief �\�P�b�g�N���X
*/
class Socket {
public:
    /**
    * �R���X�g���N�^
    */
    Socket();
    /**
    * �R���X�g���N�^
    * @param address �\�P�b�g�A�h���X
    */
    Socket(const InetSocketAddress& address);
    /**
    * �R���X�g���N�^
    * @param address �A�h���X
    * @param port �|�[�g�ԍ�
    */
    Socket(const InetAddress& address, int port);
    /**
    * �R���X�g���N�^
    * @param host �z�X�g��
    * @param port �|�[�g�ԍ�
    */
    Socket(const std::string& host, int port);
    /**
    * �R���X�g���N�^
    * @param impl �\�P�b�g�����I�u�W�F�N�g
    */
    Socket(SocketImpl* impl);
    /**
    * �f�X�g���N�^
    */
    virtual ~Socket();
    /**
    * �\�P�b�g�̐ڑ�
    * @param address �\�P�b�g�A�h���X
    */
    void connect(const InetSocketAddress& address);
    /**
    * �\�P�b�g�̐ڑ�
    * @param address �A�h���X
    * @param port �|�[�g�ԍ�
    */
    void connect(const InetAddress& address, int port);
    /**
    * �\�P�b�g�̐ڑ�
    * @param host �z�X�g��
    * @param port �|�[�g�ԍ�
    */
    void connect(const std::string& host, int port);
    /**
    * �\�P�b�g�����
    */
    void close();
    /**
    * �ڑ���̃\�P�b�g�Ƀf�[�^�𑗐M
    * @param buffer �o�b�t�@
    * @param size �o�b�t�@�̃T�C�Y
    */
    int send(const void* buffer, int size);
    /**
    * �ڑ���̃\�P�b�g�Ƀf�[�^�𑗐M
    * @param msg ���M���郁�b�Z�[�W
    */
    int send(const std::string& msg);
    /**
    * �ڑ���̃\�P�b�g����f�[�^����M
    * @param buffer �o�b�t�@
    * @param size �o�b�t�@�̃T�C�Y
    */
    int recieve(void* buffer, int size);
    /**
    * �ڑ���̃\�P�b�g����f�[�^����M
    * @return ��M�������b�Z�[�W
    */
    std::string recieve();
    /**
    * �\�P�b�g�̃A�h���X���擾
    */
    InetAddress getAddress() const;
    /**
    * �|�[�g�ԍ����擾
    */
    int getPort() const;
    /**
    * �\�P�b�g�̃��[�J���A�h���X���擾
    */
    InetAddress getLocalAddress() const;
    /**
    * �\�P�b�g�̃��[�J���|�[�g�ԍ����擾
    */
    int getLocalPort() const;
    /**
    * �ڑ��������ׂ�
    */
    bool isConnected() const;
    /**
    * �V���b�g�_�E��
    */
    void shutDown(int how = Socket::SHUTDOWN_BOTH);
public:
    static const int SHUTDOWN_RECIEVE; //!< ��M���V���b�g�_�E��
    static const int SHUTDOWN_SEND; //!< ���M���V���b�g�_�E��
    static const int SHUTDOWN_BOTH; //!< ����M���V���b�g�_�E��
private:
    //�R�s�[�֎~
    Socket(const Socket& other) = delete;
    //�R�s�[�֎~
    Socket& operator =(const Socket& other) = delete;
private:
    std::unique_ptr<SocketImpl> mImpl; //!< �\�P�b�g�����N���X
};

} //Network 