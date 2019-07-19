#include "Transform.h"
#include "Utility/Math/Matrix4x4.h"
#include "Utility/Math/Matrix4x3.h"

Transform::Transform()
    :Transform(Math::Vector3(0.0f, 0.0f, 0.0f),
        Math::Quaternion(),
        Math::Vector3(1.0f, 1.0f, 1.0f)) {}

Transform::Transform(const Math::Vector3& position,
    const Math::Quaternion& rotate,
    const Math::Vector3& scale)
    : mParent(nullptr), mPosition(position), mRotation(rotate), mScale(scale) {}

Transform::~Transform() {}

Math::Matrix4x4 Transform::createSRTMatrix() const {
    if (mParent) {
        return  createLocalSRTMatrix() * mParent->createSRTMatrix();
    }
    return createLocalSRTMatrix();
}

Math::Matrix4x4 Transform::createLocalSRTMatrix() const {
    Math::Matrix4x3 scale;
    scale.setupScale(mScale);
    Math::Matrix4x3 rotate;
    rotate.setupRotate(mRotation);
    Math::Matrix4x3 world(scale * rotate);
    world.setTranslation(mPosition);
    return world.convertMatrix4x4();
}

void Transform::setParent(Transform* parent) {
    mParent = parent;
}
