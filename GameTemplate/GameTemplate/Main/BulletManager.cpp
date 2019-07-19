#include "BulletManager.h"
#include "Main/Bullet.h"

Main::BulletManager::BulletManager() {}

Main::BulletManager::~BulletManager() {
    mBulletList.clear();
    mAddBulletList.clear();
}

void Main::BulletManager::registerBullet(std::unique_ptr<Bullet> obj) {
    mAddBulletList.emplace_back(std::move(obj));
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
