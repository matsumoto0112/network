#pragma once

namespace Thread {
/**
* @class IRunnable
* @brief �X���b�h���s�C���^�[�t�F�[�X
*/
class IRunnable {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IRunnable() = default;
    /**
    * @brief ���s
    */
    virtual void run() = 0;
};

} //Thread 