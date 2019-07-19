#pragma once
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class EndProc
* @brief ���j���[����I�����I�΂ꂽ�Ƃ��̃v���V�[�W��
*/
class EndProc : public IWindowProc {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~EndProc();
    /**
    * @brief �E�B���h�E�v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
};

} //Window 