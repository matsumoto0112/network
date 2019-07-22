#include "Bullet.h"
#include "Device/Graphics/Model/Model.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Device/GameDevice.h"
#include "Define/Path.h"
#include "Define/Resource/Model.h"
#include "Main/BoxCollision.h"
#include "Main/ICollisionRegister.h"
#include "Utility/Resource/ResourceManager.h"

namespace Main {

Bullet::Bullet(Transform transform, Tag tag, ICollisionRegister& collisionRegister)
    :GameObject(transform, tag), mSpeed(50.0f), mCollisionRegister(collisionRegister), mIsAlive(true),
    mCollision(std::make_unique<BoxCollision>(*this, Math::OBB3D())) {
    Transform colliderTransform;
    colliderTransform.setParent(&mTransform);
    mCollision->setColliderTransform(colliderTransform);
    Math::OBB3D* obb = mCollision->getOBB();
    obb->setLength(Math::Vector3(0.25f, 0.25f, 1.0f));
    mCollisionRegister.registerCollision(mCollision.get());

    mModel = Utility::ResourceManager::getInstance().getFBXModel()->getResource(Define::ModelType::Bullet);
    mTransform.setPosition(mTransform.getPosition() + Math::Vector3(0, 0, -0.5f));
}

Bullet::~Bullet() {
    mCollisionRegister.removeCollision(mCollision.get());
}

void Bullet::update(float delta) {
    //³–Ê‚ÉŒü‚©‚Á‚Äi‚ñ‚Å‚¢‚­
    Math::Quaternion q = Math::Quaternion(0, 0, 1, 0);
    Math::Quaternion r = Math::Quaternion::conjugate(mTransform.getRotate()) * q *  mTransform.getRotate();
    Math::Vector3 v(r.x, r.y, r.z);

    mTransform.setPosition(mTransform.getPosition() + v * mSpeed * delta);
}

void Bullet::draw() {
    mModel->draw(mTransform);
}

void Bullet::hit(GameObject& other) {
    if (other.getTag() == Tag::Wall) {
        mIsAlive = false;
    }
}

} //Main 
