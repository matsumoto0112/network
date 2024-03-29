#pragma once
#include <initializer_list>

namespace Math {

/*! 円周率π*/
static const float PI = 3.1415926f;
/*! 2π*/
static const float PI2 = PI * 2;

/*! 計算許容誤差*/
static const float EPSILON = 0.001f;

/**
* @class MathUtility
* @brief 数学関係のユーティリティクラス
*/
class MathUtility {
public:
    /**
    * @brief クランプ処理
    * @tparam t クランプする値
    * @tparam min 下限値
    * @tparam max 上限値
    * @return クランプされた値
    */
    template<class T>
    static T& clamp(T& t, const T& min, const T& max);

    /**
    * @brief サイン
    */
    static float sin(float degree);

    /**
    * @brief コサイン
    */
    static float cos(float degree);

    /**
    * @brief タンジェント
    */
    static float tan(float degree);

    /**
    * @brief アークタンジェント
    * @return 角度(deg)を返す
    */
    static float atan2(float y, float x);

    /**
    * @brief アークサイン
    * @return 角度（deg）を返す
    */
    static float asin(float x);

    static float acos(float x);

    /**
    * @brief ルート
    */
    static float sqrt(float a);

    /**
    * @brief コタンジェント(cot)
    */
    static float cot(float degree);

    /**
    * @brief 度からラジアンへ変換する
    * @param deg 度
    * @return 変換されたラジアン
    */
    static float toRadian(float deg);

    /**
    * @brief ラジアンから度へ変換する
    * @param rad ラジアン
    * @return 変換された度
    */
    static float toDegree(float rad);

    /**
    * @brief 絶対値
    */
    static float abs(float X);

    /**
    * @brief 補間
    * @tparam a 開始値
    * @tparam b 終了値
    * @tparam t 補間値（０〜１）
    */
    template <class T>
    static T lerp(const T& a, const T& b, float t);

    /**
    * @brief 最大値の取得
    */
    static float mymax(const std::initializer_list<float>& param);
    /**
    * @brief 最小値の取得
    */
    static float mymin(const std::initializer_list<float>& param);
};

/**
* @brief クランプ処理
* @tparam t クランプする値
* @tparam min 下限値
* @tparam max 上限値
* @return クランプされた値
*/
template<class T>
T& MathUtility::clamp(T& t, const T& min, const T& max) {
    if (t < min)t = min;
    else if (t > max) t = max;
    return t;
}

template<class T>
inline T MathUtility::lerp(const T& a, const T& b, float t) {
    //0〜1にクランプ
    t = clamp(t, 0.0f, 1.0f);
    return a * (1.0f - t) + b * t;
}

} //Math
