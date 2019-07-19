#pragma once
#include <string>

namespace Define {

/**
* @class Debug
* @brief デバッグ用情報定義
*/
class Debug {
public:
    static const bool ENABLE_DEBUG_WINDOW; //!< デバッグウィンドウを有効にするか
    static const int DEBUG_WINDOW_WIDTH; //!< デバッグウィンドウの幅
    static const int DEBUG_WINDOW_HEIGHT; //!< デバッグウィンドウの高さ
    static const int DEBUG_WINDOW_POSITION_X; //!< デバッグウィンドウのX座標　
    static const int DEBUG_WINDOW_POSITION_Y; //!< デバッグウィンドウのY座標
    static const std::string DEBUG_WINDOW_TITLE; //!< デバッグウィンドウタイトル
};

} //Define 