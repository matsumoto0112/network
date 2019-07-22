#pragma once
#include "Main/GameObject.h"

namespace Graphics {
class Model;
} //Graphics 

namespace Main {
class BoxCollision;
class ICollisionRegister;

class Bullet : public GameObject {
public:
    Bullet(Transform transform, Tag tag, ICollisionRegister& collisionRegister);
    virtual ~Bullet();
    virtual void update(float delta) override;
    virtual void draw() override;
    virtual void hit(GameObject& other) override;
    bool isAlive() const { return mIsAlive; }
private:
    float mSpeed;
    ICollisionRegister& mCollisionRegister;
    std::shared_ptr<Graphics::Model> mModel;
    std::unique_ptr<BoxCollision> mCollision;
    bool mIsAlive;
};

} //Main 