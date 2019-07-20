#include "MainObjectManager.h"
#include "GameObject.h"
#include "Main/Player.h"
#include "Main/Enemy.h"
#include "Main/Stage.h"
#include "Main/Bullet.h"
#include "Network/PacketData.h"
#include "Main/BulletManager.h"
#include "Main/CollisionManager.h"
#include "Utility/Debug.h"

namespace Main {

MainObjectManager::MainObjectManager(ShootSendOpponentFunc func)
    :mBulletManager(std::make_unique<BulletManager>(*this)),
    mCollisionManager(std::make_unique<CollisionManager>()),
    mSendFunc(func) {}


MainObjectManager::~MainObjectManager() {}

void MainObjectManager::registerPlayer(std::unique_ptr<Player> player) {
    mPlayer = std::move(player);
}

void MainObjectManager::registerEnemy(std::unique_ptr<Enemy> enemy) {
    mEnemy = std::move(enemy);
}

void MainObjectManager::registerStage(std::unique_ptr<Stage> stage) {
    mStage = std::move(stage);
}

void MainObjectManager::update(float delta) {
    MY_ASSERTION(mPlayer != nullptr, "プレイヤーが存在しません");
    MY_ASSERTION(mEnemy != nullptr, "エネミーが存在しません");
    MY_ASSERTION(mStage != nullptr, "ステージが存在しません");

    mPlayer->update(delta);
    mEnemy->update(delta);
    mStage->update(delta);

    mBulletManager->update(delta);
    mCollisionManager->update();
}

void MainObjectManager::draw() {
    mPlayer->draw();
    mEnemy->draw();
    mStage->draw();

    mBulletManager->draw();
}

Network::TransformData MainObjectManager::createTransformData() const {
    Network::TransformData result;
    result.position = mPlayer->getTransform().getPosition();
    result.rotate = mPlayer->getTransform().getRotate();
    return result;
}

void MainObjectManager::recieveTransformData(const Network::TransformData& data) {
    mEnemy->recieveTransformData(data);
}

void MainObjectManager::shoot(const Math::Vector3& position, const Math::Quaternion& rotate) {
    MY_ASSERTION(mSendFunc != nullptr, "ショットを相手に通知する関数が登録されていません");

    mBulletManager->shoot(position, rotate);
    mSendFunc(position, rotate);
}

void MainObjectManager::shootByOpponent(const Math::Vector3& position, const Math::Quaternion& rotate) {
    mBulletManager->shootByOpponent(position, rotate);
}

void MainObjectManager::registerCollision(BoxCollision* collision) {
    mCollisionManager->registerCollision(collision);
}

} //Main 
