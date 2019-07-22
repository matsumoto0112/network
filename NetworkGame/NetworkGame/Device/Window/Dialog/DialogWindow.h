#pragma once
#include <Windows.h>

namespace Window {
class Window;

/**
* @class DialogWindow
* @brief �_�C�A���O�E�B���h�E�N���X
*/
class DialogWindow {
public:
    /**
    * @brief �R���X�g���N�^
    * @param mainWindow ���C���E�B���h�E�n���h��
    * @param dialogID �쐬����_�C�A���OID
    * @param dlgProc �_�C�A���O����������v���V�[�W��
    */
    DialogWindow(Window* parentWindow, UINT dialogID, DLGPROC dlgProc);
    /**
    * @brief �f�X�g���N�^
    */
    ~DialogWindow();
    /**
    * @brief �_�C�A���O�����
    */
    void close();
    /**
    * @brief �n���h���̎擾
    */
    HWND getHandle() const { return mDlgHandle; }
    bool isEnd() const { return mIsEnd; }
private:
    HWND mDlgHandle; //!< �_�C�A���O�n���h��
    bool mIsEnd;
};

} //Window 