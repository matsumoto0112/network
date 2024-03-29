#pragma once

#include <array>
#include <ostream>
#include "Utility/Math/Vector3.h"

namespace Math {

class Vector2;
class Matrix3x3;
class Quaternion;

/**
* @class Matrix4x4
* @brief 4*4行列
*/
class Matrix4x4 {
public:
    std::array<std::array<float, 4>, 4> m; //!< 4x4行列
    /**
    * @brief コンストラクタ
    */
    Matrix4x4();
    /**
    * @brief コンストラクタ
    */
    Matrix4x4(float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44);
    /**
    * @brief コンストラクタ
    */
    Matrix4x4(std::array<std::array<float, 4>, 4> m);
    /**
    * @brief 単位行列化
    */
    void loadIdentity();
    /**
    * @brief 単位行列を返す
    */
    static Matrix4x4 identity();
    /**
    * @brief 代入演算子
    */
    Matrix4x4& operator=(const Matrix4x4& mat);
    /**
    * @brief 等値演算子
    */
    bool operator==(const Matrix4x4& mat) const;
    /**
    * @brief 等値演算子
    */
    bool operator!=(const Matrix4x4& mat) const;
    /**
    * @brief 単項プラス演算子
    */
    Matrix4x4 operator+();
    /**
    * @brief 単項マイナス演算子
    */
    Matrix4x4 operator-();
    /**
    * @brief 加算
    */
    Matrix4x4 operator+(const Matrix4x4& mat) const;
    /**
    * @brief 減算
    */
    Matrix4x4 operator-(const Matrix4x4& mat) const;
    /**
    * @brief スカラー倍
    */
    Matrix4x4 operator*(float k) const;
    /**
    * @brief 乗算
    */
    Matrix4x4 operator*(const Matrix4x4& mat) const;
    /**
    * @brief ベクトル×行列
    */
    friend Vector3 operator*(const Vector3& v, const Matrix4x4& mat);
    /**
    * @brief スカラー除算
    */
    Matrix4x4 operator/(float k) const;
    /**
    * @brief 加算代入演算子
    */
    Matrix4x4& operator+=(const Matrix4x4& mat);
    /**
    * @brief 減算代入演算子
    */
    Matrix4x4& operator-=(const Matrix4x4& mat);
    /**
    * @brief 乗算代入演算子
    */
    Matrix4x4& operator*=(float k);
    /**
    * @brief 乗算代入演算子
    */
    Matrix4x4& operator*=(const Matrix4x4& mat);
    /**
    * @brief ベクトル×行列
    */
    friend Vector3& operator*=(Vector3& v, const Matrix4x4& mat);
    /**
    * @brief 除算代入演算子
    */
    Matrix4x4& operator/=(float k);

    /**
    * @brief 平行移動行列の作成
    * @param v 移動量
    */
    static Matrix4x4 createTranslate(const Vector3& v);
    /**
    * @brief 平行移動行列の作成
    * @param x 移動量X
    * @param y 移動量Y
    * @param z 移動量Z
    */
    static Matrix4x4 createTranslate(float x, float y, float z);
    /**
    * @brief 平行移動行列のセットアップ
    * @param v 移動量
    */
    Matrix4x4& setupTransform(const Vector3& v);
    /**
    * @brief 平行移動行列のセットアップ
    * @param x 移動量X
    * @param y 移動量Y
    * @param z 移動量Z
    */
    Matrix4x4& setupTransform(float x, float y, float z);

    /**
    * @brief 平行移動
    * @param v 移動量
    * @return 今の行列からさらにv移動した後の行列を返す
    */
    Matrix4x4& move(const Vector3& v);

    /**
    * @brief 平行移動
    * @param x 移動量X
    * @param y 移動量Y
    * @param z 移動量Z
    * @return 今の行列からさらに(x,y,z)移動した後の行列を返す
    */
    Matrix4x4& move(float x, float y, float z);

    /**
    * @brief X軸回転行列の作成
    * @param degree 回転量(度)
    */
    static Matrix4x4 createRotationX(float degree);
    /**
    * @brief X軸回転行列のセットアップ
    * @param degree 回転量(度)
    */
    Matrix4x4& setupRotationX(float degree);
    /**
    * @brief Y軸回転行列の作成
    * @param degree 回転量(度)
    */
    static Matrix4x4 createRotationY(float degree);
    /**
    * @brief Y軸回転行列のセットアップ
    * @param degree 回転量(度)
    */
    Matrix4x4& setupRotationY(float degree);
    /**
    * @brief Z軸回転行列の作成
    * @param degree 回転量(度)
    */
    static Matrix4x4 createRotationZ(float degree);
    /**
    * @brief Z軸回転行列のセットアップ
    * @param degree 回転量(度)
    */
    Matrix4x4& setupRotationZ(float degree);
    /**
    * @brief 回転行列の作成
    * @param r 各軸の回転量(度)
    */
    static Matrix4x4 createRotation(const Vector3& r);
    /**
    * @brief 回転行列のセットアップ
    * @param r 各軸の回転量(度)
    */
    Matrix4x4& setupRotation(const Vector3& r);
    /**
    * @brief X軸回転
    * @param degree 回転量(度)
    * @return 今の行列からさらにdegree度回転する行列を返す
    */
    Matrix4x4& rotateX(float degree);
    /**
    * @brief Y軸回転
    * @param degree 回転量(度)
    * @return 今の行列からさらにdegree度回転する行列を返す
    */
    Matrix4x4& rotateY(float degree);
    /**
    * @brief Z軸回転
    * @param degree 回転量(度)
    * @return 今の行列からさらにdegree度回転する行列を返す
    */
    Matrix4x4& rotateZ(float degree);
    /**
    * @brief 回転
    * @param r 各軸の回転量(度)
    * @return 今の行列からさらにv度回転する行列を返す
    */
    Matrix4x4& rotate(const Vector3& v);

    /**
    * @brief 拡大・縮小行列の作成
    * @param s 拡大・縮小の大きさ(各軸共通)
    */
    static Matrix4x4 createScale(float s);
    /**
    * @brief 拡大・縮小行列の作成
    * @param s 各軸の拡大・縮小の大きさ
    */
    static Matrix4x4 createScale(const Vector3& s);
    /**
    * @brief 拡大・縮小行列のセットアップ
    * @param s 拡大・縮小の大きさ(各軸共通)
    */
    Matrix4x4& setupScale(float s);
    /**
    * @brief 拡大・縮小行列のセットアップ
    * @param s 各軸の拡大・縮小の大きさ
    */
    Matrix4x4& setupScale(const Vector3& s);
    /**
    * @brief 拡大・縮小行列の作成
    * @param sx x軸の拡大・縮小の大きさ
    * @param sy y軸の拡大・縮小の大きさ
    * @param sz z軸の拡大・縮小の大きさ
    */
    static Matrix4x4 createScale(float sx, float sy, float sz);
    /**
    * @brief 拡大・縮小行列
    * @param s 拡大・縮小の大きさ(各軸共通)
    * @return 今の行列からさらにs倍拡大する行列を返す
    */
    Matrix4x4& scale(float s);
    /**
    * @brief 拡大・縮小行列
    * @param s 各軸の拡大・縮小の大きさ
    * @return 今の行列からさらにs倍拡大する行列を返す
    */
    Matrix4x4& scale(const Vector3& s);

    /**
    * @brief ビュー行列の作成
    * @param eye 視点
    * @param at 注視点
    * @param up カメラの上方向
    */
    static Matrix4x4 createView(const Vector3& eye, const Vector3& at, const Vector3& up);

    /**
    * @brief ビュー行列のセットアップ
    * @param eye 視点
    * @param at 注視点
    * @param up カメラの上方向
    */
    Matrix4x4& setUpView(const Vector3& eye, const Vector3& at, const Vector3& up);

    /**
    * @brief プロジェクション行列の作成
    * @param fovY 視野角(度)
    * @param screenX スクリーンの幅
    * @param screenY スクリーンの高さ
    * @param near 最近点
    * @param far 最遠点
    */
    static Matrix4x4 createProjection(float fovY, float screenX, float screenY, float near, float far);

    /**
    * @brief プロジェクション行列のセットアップ
    * @param fovY 視野角(度)
    * @param screenX スクリーンの幅
    * @param screenY スクリーンの高さ
    * @param near 最近点
    * @param far 最遠点
    */
    Matrix4x4& setProjection(float fovY, float screenX, float screenY, float near, float far);

    Math::Vector3 getTranslate();

    /**
    * @brief 正投影行列の作成
    * @param screenSize 画面の大きさ
    */
    static Matrix4x4 createOrthographic(const Vector2& screenSize);
    /**
    * @brief 正投影行列のセットアップ
    * @param screenSize 画面の大きさ
    */
    Matrix4x4& setUpOrthographic(const Vector2& screenSize);

    /**
    * @brief 四元数に変換
    */
    Quaternion toQuaternion() const;

    /**
    * @brief 転置する
    */
    Matrix4x4& transpose();

    /**
    * @brief 転置行列
    */
    static Matrix4x4 transposition(const Matrix4x4& mat);
    /**
    * @brief 行列式を求める
    * @param mat 求める行列
    */
    static float determinant(const Matrix4x4& mat);
    /**
    * @brief 逆行列を求める
    * @param mat 求める行列
    */
    static Matrix4x4 inverse(const Matrix4x4& mat);

    /**
    * @brief 3*3行列に変換(余分なデータ切り捨て)
    */
    static Matrix3x3 toMatrix3(const Matrix4x4& mat);

    static Matrix4x4 lerp(const Matrix4x4& mat1, const Matrix4x4& mat2, float t);

    friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat);
};

} //Math