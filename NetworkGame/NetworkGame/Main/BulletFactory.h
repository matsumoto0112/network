#pragma once
#include <memory>
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Quaternion.h"

namespace Main {
class Bullet;
class ICollisionRegister;
enum class Tag;

/**
* @class BulletFactory
* @brief 弾の生成者
*/
class BulletFactory {
public:
    /**
    * @brief コンストラクタ
    */
    BulletFactory(ICollisionRegister& collisionRegister);
    /**
    * @brief デストラクタ
    */
    ~BulletFactory();
    std::unique_ptr<Bullet> createBullet(const Math::Vector3& position, const Math::Quaternion& rotate, Tag tag);
private:
    ICollisionRegister& mCollisionRegister;
};

} //Main 