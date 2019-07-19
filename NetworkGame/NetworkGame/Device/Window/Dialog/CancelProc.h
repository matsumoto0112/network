#pragma once

#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class CancelProc
* @brief �_�C�A���O�ŃL�����Z���������ꂽ�Ƃ��̃v���V�[�W��
*/
class CancelProc : public IWindowProc {
    using CancelFunc = std::function<void(void)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param cancelFunc �L�����Z���������ꂽ�Ƃ��̃C�x���g
    */
    CancelProc(CancelFunc cancelFunc);
    /**
    * @brief �f�X�g���N�^
    */
    ~CancelProc();
    /**
    * @brief �v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) override;
private:
    CancelFunc mFunc; //!< �L�����Z���������ꂽ�Ƃ��̃C�x���g�֐�
};
} //Window 