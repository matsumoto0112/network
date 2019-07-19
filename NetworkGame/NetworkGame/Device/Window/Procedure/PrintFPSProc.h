#pragma once
#include "Device/Window/Procedure/IWindowProc.h"
#include "Device/Window/Procedure/MenuCheckedController.h"
#include <functional>

namespace Window {

/**
* @class PrintFPSProc
* @brief FPS�\�����I�����ꂽ�Ƃ��̃v���V�[�W��
*/
class PrintFPSProc : public IWindowProc {
    using PrintFunc = std::function<void(void)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param hWnd �E�B���h�E�n���h��
    * @param func FPS��\�������邽�߂ɌĂԊ֐�
    */
    PrintFPSProc(HWND hWnd, PrintFunc func);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~PrintFPSProc();
    /**
    * @brief �E�B���h�E�v���V�[�W��
    */
    virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL* isReturn) override;
private:
    PrintFunc mFunc; //!< �\�������邽�߂̊֐�
    MenuCheckedController mMenuCheckedController; //!< ���j���[�̃`�F�b�N�Ǘ�
};

} //Window 