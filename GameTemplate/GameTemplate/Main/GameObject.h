#pragma once
#include "Utility/Transform.h"

namespace Main {

class GameObject {
public:
    GameObject(Transform transform) :mTransform(transform) {};
    virtual ~GameObject() = default;
    virtual void update(float delta) {};
    virtual void draw() {};
    const Transform& getTransform() const { return mTransform; }

    virtual void hit(GameObject& other) {};
protected:
    Transform mTransform;
};

} //Main 