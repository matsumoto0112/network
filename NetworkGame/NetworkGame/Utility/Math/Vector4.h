#pragma once

#include <ostream>
#include "Utility/Math/MathUtility.h"

namespace Math {

/**
* @class Vector4
* @brief 4次元ベクトル
*/
class Vector4 {
public:
    float x; //!< x成分
    float y; //!< y成分
    float z; //!< z成分
    float w; //!< w成分

    /**
    * @brief コンストラクタ
    */
    Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
    /**
    * @brief コピーコンストラクタ
    */
    Vector4(const Vector4& v);
    /**
    * @brief 代入演算子
    */
    Vector4& operator =(const Vector4& a);

    /**
    * @brief 等値演算子
    */
    bool operator ==(const Vector4 &a) const;
    /**
    * @brief 等値演算子
    */
    bool operator !=(const Vector4 &a) const;
    /**
    * @brief 0ベクトルの取得
    */
    static Vector4 zero();
    /**
    * @brief 単項プラス演算子
    */
    Vector4 operator +() const;
    /**
    * @brief 単項マイナス演算子
    */
    Vector4 operator -() const;
    /**
    * @brief 加算
    */
    Vector4 operator +(const Vector4 &a) const;
    /**
    * @brief 減算
    */
    Vector4 operator -(const Vector4 &a) const;
    /**
    * @brief スカラー倍
    */
    Vector4 operator *(float a) const;
    /**
    * @brief スカラー除算
    */
    Vector4 operator /(float a) const;
    /**
    * @brief スカラー倍
    */
    friend Vector4 operator *(float a, const Vector4& v);
    /**
    * @brief スカラー除算
    */
    friend Vector4 operator /(float a, const Vector4& v);
    /**
    * @brief 加算代入演算子
    */
    Vector4 &operator +=(const Vector4 &a);
    /**
    * @brief 減算代入演算子
    */
    Vector4 &operator -=(const Vector4 &a);
    /**
    * @brief 乗算代入演算子
    */
    Vector4 &operator *=(float a);
    /**
    * @brief 除算代入演算子
    */
    Vector4 &operator /=(float a);

    /**
    * @brief 大きさの2乗を返す
    * @return ベクトルの大きさの2乗
    */
    float lengthSq() const;
    /**
    * @brief 大きさを返す
    * @return ベクトルの大きさ
    */
    float length() const;
    /**
    * @brief ベクトルを正規化する
    */
    void normalize();
    /**
    * @brief ベクトルの正規化
    * @return 正規化されたベクトルを返す
    */
    Vector4 getNormal() const;
    /**
    * @brief 内積
    * @param a 計算するベクトル
    * @return 内積
    */
    float dot(const Vector4 &a) const;
    /**
    * @brief ベクトルのクランプ処理
    * @param min 下限
    * @param max 上限
    */
    void clamp(const Vector4& min, const Vector4& max);

    friend std::ostream& operator<<(std::ostream& oss, const Math::Vector4& v);
};

/**
* @brief 内積
* @param a ベクトル1
* @param b ベクトル2
* @return a・b
*/
inline float dot(const Vector4 &a, const Vector4 &b) {
    return a.dot(b);
}

} //Math
