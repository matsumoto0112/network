#pragma once
#include "Utility/Math/Vector4.h"
#include "Utility/Math/Vector3.h"

namespace Math {

class Plane {
public:
    /**
    * @brief コンストラクタ
    * @param normal 平面の法線ベクトル
    * @param point 平面上の任意の一点
    */
    Plane(Vector3 normal, Vector3 point);
    ~Plane();
private:
    Vector4 mPlaneVector;
};

} //Math 