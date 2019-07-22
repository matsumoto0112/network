#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Device/Window/Procedure/IWindowProc.h"

namespace Window {
enum class DialogProcType {
    Client,
    Server,
};

/**
* @class DialogProcedures
* @brief �_�C�A���O�̃v���V�[�W���Ǘ��N���X
*/
class DialogProcedures {
private:
    using WindowProcPtr = std::unique_ptr<IWindowProc>;
    using WindowProcContainer = std::vector<WindowProcPtr>;
public:
    /**
    * @brief �N���C�A���g�p�_�C�A���O�v���V�[�W��
    */
    static BOOL CALLBACK ClientDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    /**
    * @brief �T�[�o�[�p�_�C�A���O�v���V�[�W��
    */
    static BOOL CALLBACK ServerDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
public:
    static IWindowProc* addProcedure(DialogProcType type, IWindowProc* proc);
    static void removeProcedure(DialogProcType type, IWindowProc* procIt);
private:
    //static WindowProcContainer mClientDlgProc; //!< �N���C�A���g�p�v���V�[�W�����X�g
    //static WindowProcContainer mServerDlgProc; //!< �T�[�o�[�p�v���V�[�W�����X�g
    static std::unordered_map<DialogProcType, WindowProcContainer> mProceduresContainer;
};

} //Window 