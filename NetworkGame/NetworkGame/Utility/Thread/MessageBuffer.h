#pragma once

#include <string>
#include <ostream>
#include <list>
#include "Utility/Thread/CriticalSection.h"

namespace Thread {

/**
* @class MessageBuffer
* @brief ���b�Z�[�W�o�b�t�@�N���X
*/
class MessageBuffer {
public:
    /**
    * @brief �R���X�g���N�^
    * @param bufferSize ���b�Z�[�W�̍ő吔
    */
    MessageBuffer(unsigned int bufferSize);
    /**
    * @brief �f�X�g���N�^
    */
    ~MessageBuffer();
    /**
    * @brief ���b�Z�[�W�̏���
    */
    void clear();
    /**
    * @brief ���b�Z�[�W�̒ǉ�
    * @param message �ǉ����郁�b�Z�[�W
    */
    void add(const std::string& message);
    /**
    * @brief �擪�̃��b�Z�[�W�̎擾
    */
    std::string getMessage();
    /**
    * @brief ���ׂẴ��b�Z�[�W�̎擾
    * @details ��M�������Ԃŕ���ł���
    */
    std::list<std::string> getAllMessage();
private:
    using MessageContainer = std::list<std::string>;
    MessageContainer mBuffer; //!< ���b�Z�[�W�o�b�t�@
    MessageContainer::size_type mBufferSize; //!< ���b�Z�[�W�̍ő吔
    CriticalSection mBufferLock; //!< �o�b�t�@�p�N���e�B�J���Z�N�V����
};
} //Thread
