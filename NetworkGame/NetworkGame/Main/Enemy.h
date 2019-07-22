#pragma once
#include <memory>
#include "Main/GameObject.h"

namespace Network {
class TransformData;
} //Network 

namespace Graphics {
class Model;
} //Graphics 

namespace Main {
class BoxCollision;
class ICollisionRegister;

class Enemy :public GameObject {
public:
    Enemy(ICollisionRegister& collisionRegister);
    virtual ~Enemy();
    virtual void update(float delta) override;
    virtual void draw() override;
    void recieveTransformData(const Network::TransformData& data);
    virtual void hit(GameObject& other) override;
private:
    std::shared_ptr<Graphics::Model> mModel;
    std::unique_ptr<BoxCollision> mCollision;
};

} //Main 