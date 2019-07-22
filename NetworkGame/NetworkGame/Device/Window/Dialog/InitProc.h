#pragma once

#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class InitProc
* @brief �_�C�A���O���������̃v���V�[�W��
*/
class InitProc : public IWindowProc {
public:
    /**
    * @brief �R���X�g���N�^
    */
    InitProc();
    /**
    * @brief �f�X�g���N�^
    */
    ~InitProc();
    /**
    * @brief �v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL * isReturn) override;
};
} //Window 