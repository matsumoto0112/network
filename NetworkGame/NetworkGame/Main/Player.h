#pragma once
#include <memory>
#include <functional>
#include "Main/GameObject.h"

namespace Graphics {
class Model;
class FPSCamera;
} //Graphics 

namespace Main {
class Bullet;
class BoxCollision;
class IShooter;
class ICollisionRegister;

class Player : public GameObject {
public:
    Player(IShooter& bulletRegister, ICollisionRegister& collisionRegister);
    ~Player();
    virtual void update(float delta) override;
    virtual void draw() override;
    virtual void hit(GameObject& other) override;
private:
    std::shared_ptr<Graphics::Model> mPlayer;
    std::unique_ptr<BoxCollision> mBoxCollision;
    Graphics::FPSCamera& mPlayerCamera;
    IShooter& mBulletRegister;
    ICollisionRegister& mCollisionRegister;
};

} //Main 