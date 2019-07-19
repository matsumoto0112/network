#pragma once
#include <string>
#include <Windows.h>

namespace Utility {

/**
* @class Console
* @brief �R���\�[���E�B���h�E�Ǘ�
* @details �d�l�����������ł��Ȃ�
*/
class Console {
public:
    /**
    * @brief �R���X�g���N�^
    * @param width ��
    * @param height ����
    * @param x �����W
    * @param y ����W
    * @param enabled �R���\�[���L���t���O
    * @param title �E�B���h�E�^�C�g��
    */
    Console(int width, int height, int x, int y,
        bool enabled,
        const std::string& title = "Console");
    /**
    * @brief �f�X�g���N�^
    */
    ~Console();
    /**
    * @brief ��ʃN���A
    */
    void clear();
    /**
    * @brief ���b�Z�[�W�o��
    * @param mes ���b�Z�[�W
    */
    void print(const std::string& mes);
private:
    bool mEnabled; //!< �R���\�[����L���ɂ��邩�ǂ���
    HANDLE mHandle; //!< �R���\�[���n���h��
    COORD mTopLeft; //!< �R���\�[���̍���
};

} //Utility 