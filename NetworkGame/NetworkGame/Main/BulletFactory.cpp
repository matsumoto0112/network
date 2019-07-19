#include "BulletFactory.h"
#include "Main/Bullet.h"
#include "Main/ICollisionRegister.h"

namespace Main {

BulletFactory::BulletFactory(ICollisionRegister& collisionRegister)
    :mCollisionRegister(collisionRegister) {}

BulletFactory::~BulletFactory() {}

std::unique_ptr<Bullet> BulletFactory::createBullet(const Math::Vector3& position, const Math::Quaternion& rotate) {
    Transform transform(position, rotate, Math::Vector3(1.0f, 1.0f, 1.0f));
    return std::make_unique<Bullet>(transform, mCollisionRegister);
}
} //Main 
