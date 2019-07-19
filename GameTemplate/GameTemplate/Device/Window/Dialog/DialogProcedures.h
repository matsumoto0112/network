#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {

/**
* @class DialogProcedures
* @brief �_�C�A���O�̃v���V�[�W���Ǘ��N���X
*/
class DialogProcedures {
public:
    /**
    * @brief �N���C�A���g�p�_�C�A���O�v���V�[�W��
    */
    static BOOL CALLBACK ClientDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    /**
    * @brief �T�[�o�[�p�_�C�A���O�v���V�[�W��
    */
    static BOOL CALLBACK ServerDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
private:
    using WindowProcPtr = std::unique_ptr<IWindowProc>;
    using WindowProcContainer = std::vector<WindowProcPtr>;
public:
    static WindowProcContainer mClientDlgProc; //!< �N���C�A���g�p�v���V�[�W�����X�g
    static WindowProcContainer mServerDlgProc; //!< �T�[�o�[�p�v���V�[�W�����X�g
};

} //Window 