#include "Bullet.h"
#include "Device/Graphics/Model/Model.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Device/GameDevice.h"
#include "Define/Path.h"
#include "Define/Resource/Model.h"
#include "Main/BoxCollision.h"
#include "Main/ICollisionRegister.h"

namespace Main {

Bullet::Bullet(Transform transform, Tag tag, ICollisionRegister& collisionRegister)
    :GameObject(transform, tag),
    mCollision(std::make_unique<BoxCollision>(*this, Math::OBB3D())) {
    Transform colliderTransform;
    colliderTransform.setParent(&mTransform);
    mCollision->setColliderTransform(colliderTransform);
    Math::OBB3D* obb = mCollision->getOBB();
    obb->setLength(0, 0.25f);
    obb->setLength(1, 0.25f);
    obb->setLength(2, 1.0f);
    collisionRegister.registerCollision(mCollision.get());

    Graphics::FBXLoader loader(Device::GameDevice::getInstance().getDirectX11Device());
    mModel = loader.load(Define::ModelName::BULLET_NAME);
    mTransform.setPosition(mTransform.getPosition() + Math::Vector3(0, 0, -0.5f));
}

Bullet::~Bullet() {}

float speed = 20.0f;
int cnt = 0;

void Bullet::update(float delta) {
    Math::Quaternion q = Math::Quaternion(0, 0, 1, 0);
    Math::Quaternion r = Math::Quaternion::conjugate(mTransform.getRotate()) * q *  mTransform.getRotate();
    Math::Vector3 v(r.x, r.y, r.z);

    mTransform.setPosition(mTransform.getPosition() + v * speed * delta);
}

void Bullet::draw() {
    mModel->draw(mTransform);
}

void Bullet::hit(GameObject& other) {}

} //Main 
