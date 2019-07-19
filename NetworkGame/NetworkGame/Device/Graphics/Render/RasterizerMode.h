#pragma once

#include "Utility/HashCombine.h"

namespace Graphics {

/**
* @enum FillMode
* @brief 描画時のフィルモード設定
*/
enum class FillMode {
    Solid, //!< 面塗りつぶし
    WireFrame, //!< ワイヤーフレーム
};

/**
* @enum CullMode
* @brief カリングモードの設定
*/
enum class CullMode {
    Front, //!< 前面カリング
    Back, //!< 背面カリング
    None, //!< カリングなし
};

/**
* @struct RasterizerMode
* @brief ラスタライザの設定構造体
*/
struct RasterizerMode {
    CullMode mCullMode;
    FillMode mFillMode;

    /**
    * @brief ハッシュ値
    */
    size_t getHash() const {
        size_t hash = 0;
        hash = Utility::combineHash(hash, mCullMode);
        hash = Utility::combineHash(hash, mFillMode);
        return hash;
    }
};

/**
* @struct RasterizerModeHash
* @brief ハッシュ値取得用関数オブジェクト
*/
struct RasterizerModeHash {
    size_t operator()(const RasterizerMode &r) const { return r.getHash(); }
};

/**
* @struct RasterizerModeEqual
* @brief  等号演算用関数オブジェクト
*/
struct RasterizerModeEqual {
    bool operator ()(const RasterizerMode& left, const RasterizerMode& right) const {
        return left.mCullMode == right.mCullMode &&left.mFillMode == right.mFillMode;
    }
};

} //Graphics 