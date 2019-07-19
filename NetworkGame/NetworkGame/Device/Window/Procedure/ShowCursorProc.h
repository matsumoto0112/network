#pragma once

#include <functional>
#include "Device/Window/Procedure/IWindowProc.h"
#include "Device/Window/Procedure/MenuCheckedController.h"

namespace Window {

/**
* @class ShowCursorProc
* @brief �J�[�\���̕\�����I�����ꂽ�Ƃ��̃v���V�[�W��
*/
class ShowCursorProc :public IWindowProc {
    using CursorEvent = std::function<void()>;
    using CursorToggleEvent = std::function<void(bool)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param hWnd �E�B���h�E�n���h��
    * @param showEvent �J�[�\���\�����̃C�x���g
    * @param hideEvent �J�[�\����\�����̃C�x���g
    */
    ShowCursorProc(HWND hWnd, CursorEvent showEvent, CursorEvent hideEvent);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ShowCursorProc();
    /**
    * @brief �E�B���h�E�v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
private:
    MenuCheckedController mMenuCheckedController; //!< ���j���[�̃`�F�b�N�Ǘ�
    CursorToggleEvent mEvent; //!< �J�[�\���̕\����\���C�x���g
};
} //Window 
