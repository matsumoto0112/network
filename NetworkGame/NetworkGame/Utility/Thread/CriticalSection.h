#pragma once

#include <Windows.h>

namespace Thread {

/**
* @class CriticalSection
* @brief �N���e�B�J���Z�N�V�����N���X
*/
class CriticalSection {
public:
    /**
    * @brief �R���X�g���N�^
    */
    CriticalSection();
    /**
    * @brief �f�X�g���N�^
    */
    ~CriticalSection();
    /**
    * @brief �N���e�B�J���Z�N�V�����J�n
    */
    void enter();
    /**
    * @brief �N���e�B�J���Z�N�V�����I��
    */
    void leave();

    /**
    * @class Lock
    * @brief ���b�N�N���X
    */
    class Lock {
    public:
        /**
        * @brief �R���X�g���N�^
        */
        Lock(CriticalSection& cs);
        /**
        * @brief �f�X�g���N�^
        */
        ~Lock();
    private:
        CriticalSection& mCriticalSection; //!< �N���e�B�J���Z�N�V����
    };
private:
    CRITICAL_SECTION mCriticalSection; //!< �N���e�B�J���Z�N�V����
};
} //Thread 
