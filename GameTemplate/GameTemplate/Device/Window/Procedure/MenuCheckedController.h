#pragma once
#include <Windows.h>

namespace Window {

/**
* @class MenuCheckedController
* @brief ���j���[�̃`�F�b�N��؂�ւ���R���g���[��
*/
class MenuCheckedController {
public:
    /**
    * @brief �R���X�g���N�^
    * @param hWnd �E�B���h�E�n���h��
    * @param itemID ���j���[�̃A�C�e��ID
    */
    MenuCheckedController(HWND hWnd,UINT itemID);
    /**
    * @brief �f�X�g���N�^
    */
    ~MenuCheckedController();
    /**
    * @brief �`�F�b�N�����Ă��邩
    * @return �`�F�b�N�����Ă�����true��Ԃ�
    */
    bool isChecked() const;
    /**
    * @brief �`�F�b�N�̃t���O�ݒ�
    */
    void setChecked(bool checked);
    /**
    * @brief �`�F�b�N�̐؂�ւ�
    */
    void switchCheckFlag();
private:
    /**
    * @brief �`�F�b�N��Ԃ̍X�V
    */
    void updateCheck();
private:
    bool mIsChecked; //!< �`�F�b�N�����Ă��邩
    HMENU mHMenu; //!< ���j���[�n���h��
    UINT mItemID; //!< �Ǘ�����A�C�e��ID
};

} //Window 