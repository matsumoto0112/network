#pragma once

#include "Network/InetAddress.h"

namespace Network {

/**
* @class InetSocketAddress
* @brief �C���^�[�l�b�g�\�P�b�g�A�h���X�Ǘ��N���X
*/
class InetSocketAddress {
public:
    /**
    * �R���X�g���N�^
    * @param address �C���^�[�l�b�g�A�h���X
    * @param port �|�[�g�ԍ�
    */
    InetSocketAddress(const InetAddress& address = InetAddress(), int port = 0);
    /**
    * �f�X�g���N�^
    */
    virtual ~InetSocketAddress();
    /**
    * �C���^�[�l�b�g�A�h���X�̎擾
    */
    const InetAddress& getInetAddress() const { return mAddress; }
    /**
    * �|�[�g�ԍ��̎擾
    */
    int getPort() const { return mPort; }
private:
    InetAddress mAddress; //!< �C���^�[�l�b�g�A�h���X
    int mPort; //!< �|�[�g�ԍ�
};
} //Network 