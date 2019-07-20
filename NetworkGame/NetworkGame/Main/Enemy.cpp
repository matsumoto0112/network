#include "Enemy.h"
#include "Device/GameDevice.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Device/Graphics/Model/Model.h"
#include "Define/Path.h"
#include "Define/Resource/Model.h"
#include "Network/PacketData.h"
#include "Main/BoxCollision.h"
#include "Main/ICollisionRegister.h"

namespace Main {

Enemy::Enemy(ICollisionRegister& collisionRegister)
    :GameObject(Transform(Math::Vector3(0, 0, 0), Math::Quaternion(), Math::Vector3(3.0f, 3.0f, 3.0f)), Tag::Enemy),
    mCollision(std::make_unique<BoxCollision>(*this, Math::OBB3D())) {
    //’·‚³‚ð’²®
    Transform colliderTransform(Math::Vector3(0, 1, 0), Math::Quaternion(), Math::Vector3(1, 2, 1));
    colliderTransform.setParent(&mTransform);
    mCollision->setColliderTransform(colliderTransform);
    //mCollision->getOBB()->setLength(1, 2.0f);
    //mCollision->getOBB()->setPosition(Math::Vector3(0, 1, 0));

    collisionRegister.registerCollision(mCollision.get());

    Graphics::FBXLoader loader(Device::GameDevice::getInstance().getDirectX11Device());
    mModel = loader.load(Define::ModelName::ENEMY_NAME);
}

Enemy::~Enemy() {}

void Enemy::update(float delta) {
}

void Enemy::draw() {
    mModel->draw(mTransform);
}

void Enemy::recieveTransformData(const Network::TransformData& data) {
    mTransform.setPosition(data.position);
    mTransform.setRotate(data.rotate);
}

void Enemy::hit(GameObject & other) {}

} //Main 
