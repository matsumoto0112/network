#include "Console.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <Windows.h>
#include "Utility/Debug.h"

namespace {
BOOL WINAPI HandlerRoutine(DWORD type) {
    switch (type) {
    case CTRL_C_EVENT:      //Ctrl+C���󂯎����
    case CTRL_BREAK_EVENT:  //Ctrl+Break���󂯎����
        return TRUE; //�����ɂ���̂�TRUE��Ԃ�
    case CTRL_CLOSE_EVENT:  //�R���\�[�������
    case CTRL_LOGOFF_EVENT: //���O�I�t����
    case CTRL_SHUTDOWN_EVENT: // �V���b�g�_�E��
        return FALSE;
    }
    return FALSE;
}
}

namespace Utility {

Console::Console(int width, int height, int x, int y, bool enabled, const std::string& title)
    :mEnabled(enabled), mTopLeft{ 0,0 } {
    if (!mEnabled)return;
    //�V�����R���\�[�����蓖��
    BOOL alloc = ::AllocConsole();

    _ASSERT_EXPR(alloc, "�R���\�[���E�B���h�E�����蓖�Ă��܂���ł���");

    //�R���\�[���o�͐抄�蓖��
    FILE* fp = nullptr;
    ::freopen_s(&fp, "CONOUT$", "w", stdout);

    //�E�B���h�E�^�C�g���̐ݒ�
    SetConsoleTitleA(title.c_str());

    //���荞�ݐ��䏈���ǉ�
    ::SetConsoleCtrlHandler(HandlerRoutine, TRUE);

    //�~�{�^���𖳌�������
    HMENU menu = ::GetSystemMenu(GetConsoleWindow(), FALSE);
    ::RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);

    //�E�B���h�E�̏ꏊ���ړ�����
    //�A�N�e�B�u�E�B���h�E������ɐ؂�ւ��̂Ŏ��O�ɃE�B���h�E���擾���Ă����Č�ŃA�N�e�B�u�ɐ؂�ւ��Ă�����
    HWND mainWindow = GetActiveWindow();
    HWND h = GetConsoleWindow();
    SetWindowPos(h,
        HWND_BOTTOM,
        x,
        y,
        width,
        height,
        SWP_NOACTIVATE | SWP_NOZORDER);
    SetForegroundWindow(mainWindow);

    //�o�͍�����
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    mHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

Console::~Console() {
    if (!mEnabled)return;
    //�R���\�[���������
    ::FreeConsole();
}

void Console::clear() {
    if (!mEnabled)return;
    if (!mHandle)mHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    //�X�N���[�����擾
    GetConsoleScreenBufferInfo(mHandle, &screen);
    //�󔒂Ŗ��߂�
    FillConsoleOutputCharacterA(
        mHandle, ' ', screen.dwSize.X * screen.dwSize.Y, mTopLeft, &written
    );
    //�F��������
    FillConsoleOutputAttribute(
        mHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, mTopLeft, &written
    );
    //�J�[�\�������Ƃ̈ʒu�ɔz�u
    SetConsoleCursorPosition(mHandle, mTopLeft);
}

void Console::print(const std::string& mes) {
    std::cout << mes << "\n";
}

} //Utility 
