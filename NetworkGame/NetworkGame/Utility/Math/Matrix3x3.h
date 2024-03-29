#pragma once

#include <array>
#include "Utility/Math/Vector2.h"

namespace Math {

class Matrix4x4;

/**
* @class Matrix3x3
* @brief 3*3行列
*/
class Matrix3x3 {
public:
    std::array<std::array<float, 3>, 3> m; //!< 3x3行列
    /**
    * @brief コンストラクタ
    */
    Matrix3x3();
    /**
    * @brief 引数付きコンストラクタ
    */
    Matrix3x3(float m11, float m12, float m13,
        float m21, float m22, float m23,
        float m31, float m32, float m33);
    /**
    * @brief 引数付きコンストラクタ
    */
    Matrix3x3(std::array<std::array<float, 3>, 3> m);
    /**
    * @brief 単位行列化
    */
    void loadIdentity();
    /**
    * @brief 単位行列を返す
    */
    static Matrix3x3 identity();
    /**
    * v代入演算子
    */
    Matrix3x3& operator=(const Matrix3x3& mat);
    /**
    * @brief 等値演算子
    */
    bool operator==(const Matrix3x3& mat) const;
    /**
    * @brief 等値演算子
    */
    bool operator!=(const Matrix3x3& mat) const;
    /**
    * @brief 単項プラス演算子
    */
    Matrix3x3 operator+();
    /**
    * @brief 単項マイナス演算子
    */
    Matrix3x3 operator-();
    /**
    * @brief 加算
    */
    Matrix3x3 operator+(const Matrix3x3& mat);
    /**
    * @brief 減算
    */
    Matrix3x3 operator-(const Matrix3x3& mat);
    /**
    * @brief スカラー倍
    */
    Matrix3x3 operator*(float k);
    /**
    * @brief 乗算
    */
    Matrix3x3 operator*(const Matrix3x3& mat);
    /**
    * @brief ベクトル×行列
    */
    friend Vector2 operator*(const Vector2& v, const Matrix3x3& mat);
    /**
    * @brief スカラー除算
    */
    Matrix3x3 operator/(float k);
    /**
    * @brief 加算代入演算子
    */
    Matrix3x3& operator+=(const Matrix3x3& mat);
    /**
    * @brief 減算代入演算子
    */
    Matrix3x3& operator-=(const Matrix3x3& mat);
    /**
    * @brief 乗算代入演算子
    */
    Matrix3x3& operator*=(float k);
    /**
    * @brief 乗算代入演算子
    */
    Matrix3x3& operator*=(const Matrix3x3& mat);
    /**
    * @brief ベクトル×行列
    */
    friend Vector2& operator*=(Vector2& v, const Matrix3x3& mat);
    /**
    * @brief 除算代入演算子
    */
    Matrix3x3& operator/=(float k);

    /**
    * @brief 平行移動行列の作成
    * @param v 移動量
    */
    static Matrix3x3 createTranslate(const Vector2& v);
    /**
    * @brief 平行移動行列の作成
    * @param x 移動量X
    * @param y 移動量Y
    */
    static Matrix3x3 createTranslate(float x, float y);

    /**
    * @brief 平行移動
    * @param v 移動量
    * @return 今の行列からさらにv移動した後の行列を返す
    */
    Matrix3x3& transform(const Vector2& v);

    /**
    * @brief 平行移動
    * @param x 移動量X
    * @param y 移動量Y
    * @return 今の行列からさらに(x,y)移動した後の行列を返す
    */
    Matrix3x3& transform(float x, float y);

    /**
    * @brief 回転行列の作成
    * @param degree 回転量(度)
    */
    static Matrix3x3 createRotate(float degree);
    /**
    * @brief 回転
    * @param degree 回転量(度)
    * @return 今の行列からさらにdegree度回転した後の行列を返す
    */
    Matrix3x3& rotate(float degree);

    /**
    * @brief 拡大・縮小行列の作成
    * @param s 拡大・縮小の大きさ(各軸共通)
    */
    static Matrix3x3 createScale(float s);
    /**
    * @brief 拡大・縮小行列の作成
    * @param s 各軸の拡大・縮小の大きさ
    */
    static Matrix3x3 createScale(const Vector2& s);

    /**
    * @brief 拡大・縮小行列
    * @param s 拡大・縮小の大きさ(各軸共通)
    * @return 今の行列からさらにs倍拡大する行列を返す
    */
    Matrix3x3& scale(float s);
    /**
    * @brief 拡大・縮小行列
    * @param s 各軸の拡大・縮小の大きさ
    * @return 今の行列からさらにs倍拡大する行列を返す
    */
    Matrix3x3& scale(const Vector2& s);

    /**
    * @brief 4*4行列への変換
    * @details 平行移動成分はなし
    */
    static Matrix4x4 toMatrix4(const Matrix3x3& mat);
};
} //Math
