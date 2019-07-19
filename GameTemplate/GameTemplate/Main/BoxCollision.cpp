#include "BoxCollision.h"
#include "Main/GameObject.h"

namespace Main {

BoxCollision::BoxCollision(GameObject& holder, const Math::OBB3D& obb)
    :mOBB(obb), mHolder(holder) {
    mHittedObjectList.clear();
}

BoxCollision::~BoxCollision() {
    mHittedObjectList.clear();
}

void BoxCollision::calculateOBBFromTransform() {
    mOBB.mPosition = mHolder.getTransform().getPosition();

    Math::Quaternion q = mHolder.getTransform().getRotate();
    mOBB.mNormalDirect[0] = q.multiply(Math::Vector3::RIGHT);
    mOBB.mNormalDirect[1] = q.multiply(Math::Vector3::UP);
    mOBB.mNormalDirect[2] = q.multiply(Math::Vector3::FORWORD);

}

void BoxCollision::checkCollide(BoxCollision& other) {
    if (other.getOBB()->isCollide(mOBB)) {
        mHittedObjectList.emplace_back(&other.mHolder);
        other.mHittedObjectList.emplace_back(&mHolder);
    }
}

void BoxCollision::noticeCollide() {
    for (auto&& obj : mHittedObjectList) {
        mHolder.hit(*obj);
    }

    mHittedObjectList.clear();
}

} //Main 
