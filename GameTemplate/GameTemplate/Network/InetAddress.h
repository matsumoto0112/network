#pragma once

#include <string>

namespace Network {

/**
* @class InetAddress
* @brief IP�A�h���X���Ǘ�����
*/
class InetAddress {
public:
    /**
    * �R���X�g���N�^
    * @param address IP�A�h���X
    */
    InetAddress(unsigned long address = InetAddress::NONE);
    /**
    * �R���X�g���N�^
    * @param address �z�X�g�A�h���X
    */
    InetAddress(const std::string& address);
    /**
    * �f�X�g���N�^
    */
    virtual ~InetAddress();
    /**
    * IP�A�h���X�̎擾
    */
    unsigned long getAddress() const { return mIPAddress; }
    /**
    * �z�X�g�A�h���X�̎擾
    */
    std::string getHostAddress() const;
public:
    /**
    * ������Z�q�I�[�o�[���[�h
    */
    InetAddress& operator =(const InetAddress& other);
    /**
    * ������Z�q�I�[�o�[���[�h
    */
    InetAddress& operator =(const std::string& host);
private:
    unsigned long mIPAddress; //!< IP�A�h���X
    static const unsigned long NONE; //!< ������IP�A�h���X
};
} //Network 
