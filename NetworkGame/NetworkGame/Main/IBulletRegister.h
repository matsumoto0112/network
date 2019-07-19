#pragma once
#include <memory>
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Quaternion.h"

namespace Main {
class Bullet;
/**
* @class IShooter
* @brief �e�����C���^�[�t�F�[�X
*/
class IShooter {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IShooter() = default;

    virtual void shoot(const Math::Vector3& position, const Math::Quaternion& rotate) = 0;
};

} //Main 