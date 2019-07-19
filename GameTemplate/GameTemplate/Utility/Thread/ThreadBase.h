#pragma once

#include "Utility/Thread/IRunnable.h"

namespace Thread {

/**
* @class ThreadBase
* @brief �X���b�h�N���X
*/
class ThreadBase : public IRunnable {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ThreadBase(IRunnable* runnable = nullptr);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ThreadBase();
    /**
    * @brief �X���b�h�̊J�n
    */
    virtual void start();
    /**
    * @brief �X���b�h�̊J�n
    */
    virtual void start(IRunnable* runnable);
    /**
    * @brief �X���b�h�̏I����ҋ@����
    */
    void join();
    /**
    * @brief �X���b�h�̎��s
    */
    virtual void run() override;
    /**
    * @brief �X���[�v����
    */
    static void sleep(unsigned int millsecond);
private:
    /**
    * @brief �R�[���o�b�N�֐�
    */
    static void callBack(void* runnable);
private:
    void* mHandle; //!< �X���b�h�n���h��
    IRunnable* mRunnable; //!< ���s����X���b�h
};

} //Thread 
