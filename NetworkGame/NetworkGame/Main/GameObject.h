#pragma once
#include "Utility/Transform.h"
#include "Main/Tag.h"

namespace Main {

class GameObject {
public:
    GameObject(Transform transform, Tag tag = Tag::NONE) :mTransform(transform), mTag(tag) {};
    virtual ~GameObject() = default;
    virtual void update(float delta) {};
    virtual void draw() {};
    const Transform& getTransform() const { return mTransform; }

    virtual void hit(GameObject& other) {};
    void setTag(Tag tag) { mTag = tag; }
    Tag getTag() const { return mTag; }
protected:
    Transform mTransform;
    Tag mTag;
};

} //Main 