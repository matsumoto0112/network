#pragma once
#include <string>
#include <Windows.h>

namespace Utility {

/**
* @class Console
* @brief コンソールウィンドウ管理
* @details 仕様上一つしか生成できない
*/
class Console {
public:
    /**
    * @brief コンストラクタ
    * @param width 幅
    * @param height 高さ
    * @param x 左座標
    * @param y 上座標
    * @param enabled コンソール有効フラグ
    * @param title ウィンドウタイトル
    */
    Console(int width, int height, int x, int y,
        bool enabled,
        const std::string& title = "Console");
    /**
    * @brief デストラクタ
    */
    ~Console();
    /**
    * @brief 画面クリア
    */
    void clear();
    /**
    * @brief メッセージ出力
    * @param mes メッセージ
    */
    void print(const std::string& mes);
private:
    bool mEnabled; //!< コンソールを有効にするかどうか
    HANDLE mHandle; //!< コンソールハンドル
    COORD mTopLeft; //!< コンソールの左上
};

} //Utility 