#include "Wall.h"
#include "Main/BoxCollision.h"
#include "Main/ICollisionRegister.h"

namespace Main {

Wall::Wall(Transform transform, ICollisionRegister& collisionRegister)
    :GameObject(transform, Tag::Wall),
    mBoxCollision(std::make_unique<BoxCollision>(*this, Math::OBB3D())) {
    mBoxCollision->setColliderTransform(mTransform);
    collisionRegister.registerCollision(mBoxCollision.get());
}

Wall::~Wall() {}

} //Main 
