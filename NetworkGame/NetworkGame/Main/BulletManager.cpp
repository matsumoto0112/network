#include "BulletManager.h"
#include "Main/Bullet.h"
#include "Main/BulletFactory.h"

Main::BulletManager::BulletManager(ICollisionRegister& collisionRegister)
    :mBulletFactory(std::make_unique<BulletFactory>(collisionRegister)) {}

Main::BulletManager::~BulletManager() {
    mBulletList.clear();
    mAddBulletList.clear();
}

void Main::BulletManager::shoot(const Math::Vector3& position, const Math::Quaternion& rotate) {
    mAddBulletList.emplace_back(mBulletFactory->createBullet(position, rotate));
}

void Main::BulletManager::update(float delta) {
    for (auto&& bullet : mBulletList) {
        bullet->update(delta);
    }
    for (auto&& add : mAddBulletList) {
        mBulletList.emplace_back(std::move(add));
    }
    mAddBulletList.clear();
}

void Main::BulletManager::draw() {
    for (auto&& bullet : mBulletList) {
        bullet->draw();
    }
}
