#pragma once
#include "Utility/Math/Vector4.h"
#include "Utility/Math/Vector3.h"

namespace Math {

class Plane {
public:
    /**
    * @brief �R���X�g���N�^
    * @param normal ���ʂ̖@���x�N�g��
    * @param point ���ʏ�̔C�ӂ̈�_
    */
    Plane(Vector3 normal, Vector3 point);
    ~Plane();
private:
    Vector4 mPlaneVector;
};

} //Math 