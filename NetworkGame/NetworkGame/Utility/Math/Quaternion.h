#pragma once
#include <iostream>

namespace Math {

class Vector3;
class Matrix4x4;

/**
* @class Quaternion
* @brief クォータニオン
*/
class Quaternion {
public:
    float x, y, z, w;
    /**
    * @brief デフォルトコンストラクタ
    */
    Quaternion();
    /**
    * v各要素で初期化
    */
    Quaternion(float x, float y, float z, float w);
    /**
    * @brief 恒等四元数化
    */
    void identity();
    /**
    * @brief  x軸に回転した角度でセットアップ
    * @param theta 回転量(rad)
    */
    void setToRotateAboutX(float theta);
    /**
    * @brief  y軸に回転した角度でセットアップ
    * @param theta 回転量(rad)
    */
    void setToRotateAboutY(float theta);
    /**
    * @brief  z軸に回転した角度でセットアップ
    * @param theta 回転量(rad)
    */
    void setToRotateAboutZ(float theta);
    /**
    * @brief  Axisを軸に回転した角度でセットアップ
    * @param theta 軸
    * @param theta 回転量(rad)
    */
    void setToRotateAboutAxis(const Vector3& axis, float theta);

    /**
    * @brief 外積
    * @detail 外積の計算方法を正式とは違う形で実装
    その理由については実例で学ぶゲーム３Ｄ数学を参照
    */
    Quaternion operator*(const Quaternion& a) const;

    /**
    * @brief 行列に変換
    */
    Matrix4x4 toMatrix() const;

    /**
    * @brief 内積
    */
    float dot(const Quaternion& a) const;

    /**
    * @brief オイラー角を取得
    */
    Vector3 toEular() const;

    static Math::Quaternion conjugate(const Math::Quaternion& q);


    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);

    static Math::Quaternion createLookTarget(const Math::Vector3& v, const Math::Vector3& normal);

    Math::Vector3 multiply(const Math::Vector3& v);
};
} // Math
