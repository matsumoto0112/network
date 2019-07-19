#include "Console.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <Windows.h>
#include "Utility/Debug.h"

namespace {
BOOL WINAPI HandlerRoutine(DWORD type) {
    switch (type) {
    case CTRL_C_EVENT:      //Ctrl+Cを受け取った
    case CTRL_BREAK_EVENT:  //Ctrl+Breakを受け取った
        return TRUE; //無効にするのでTRUEを返す
    case CTRL_CLOSE_EVENT:  //コンソールを閉じた
    case CTRL_LOGOFF_EVENT: //ログオフした
    case CTRL_SHUTDOWN_EVENT: // シャットダウン
        return FALSE;
    }
    return FALSE;
}
}

namespace Utility {

Console::Console(int width, int height, int x, int y, bool enabled, const std::string& title)
    :mEnabled(enabled), mTopLeft{ 0,0 } {
    if (!mEnabled)return;
    //新しいコンソール割り当て
    BOOL alloc = ::AllocConsole();

    _ASSERT_EXPR(alloc, "コンソールウィンドウが割り当てられませんでした");

    //コンソール出力先割り当て
    FILE* fp = nullptr;
    ::freopen_s(&fp, "CONOUT$", "w", stdout);

    //ウィンドウタイトルの設定
    SetConsoleTitleA(title.c_str());

    //割り込み制御処理追加
    ::SetConsoleCtrlHandler(HandlerRoutine, TRUE);

    //×ボタンを無効化する
    HMENU menu = ::GetSystemMenu(GetConsoleWindow(), FALSE);
    ::RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);

    //ウィンドウの場所を移動する
    //アクティブウィンドウが勝手に切り替わるので事前にウィンドウを取得しておいて後でアクティブに切り替えてあげる
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

    //出力高速化
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    mHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

Console::~Console() {
    if (!mEnabled)return;
    //コンソール解放処理
    ::FreeConsole();
}

void Console::clear() {
    if (!mEnabled)return;
    if (!mHandle)mHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    //スクリーン情報取得
    GetConsoleScreenBufferInfo(mHandle, &screen);
    //空白で埋める
    FillConsoleOutputCharacterA(
        mHandle, ' ', screen.dwSize.X * screen.dwSize.Y, mTopLeft, &written
    );
    //色を初期化
    FillConsoleOutputAttribute(
        mHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, mTopLeft, &written
    );
    //カーソルをもとの位置に配置
    SetConsoleCursorPosition(mHandle, mTopLeft);
}

void Console::print(const std::string& mes) {
    std::cout << mes << "\n";
}

} //Utility 
