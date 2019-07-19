#pragma once

#include <stdexcept>

/**
* @class SocketException
* @brief �\�P�b�g��O�N���X
*/
class SocketException : public std::runtime_error {
public:
    /**
    * �R���X�g���N�^
    * @param msg ���b�Z�[�W
    */
    SocketException(const std::string& msg)
        :std::runtime_error(msg) {}
};