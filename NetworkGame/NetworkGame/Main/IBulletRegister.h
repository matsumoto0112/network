#pragma once
#include <memory>
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Quaternion.h"

namespace Main {
class Bullet;
/**
* @class IShooter
* @brief 弾を撃つインターフェース
*/
class IShooter {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IShooter() = default;

    virtual void shoot(const Math::Vector3& position, const Math::Quaternion& rotate) = 0;
};

} //Main 