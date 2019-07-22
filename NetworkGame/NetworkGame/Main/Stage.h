#pragma once
#include <memory>
#include <vector>
#include "Utility/Transform.h"
#include "Utility/Math/Plane.h"
#include "Device/Graphics/Color4.h"

namespace Graphics {
class Model;
} //Graphics

namespace Main {
class Wall;
class ICollisionRegister;

class Stage {
public:
    Stage(ICollisionRegister& collisionRegister);
    ~Stage();
    void update(float delta);
    void draw();
private:
    std::shared_ptr<Graphics::Model> mFloor;
    Transform mFloorTransform;
    std::shared_ptr<Graphics::Model> mObjectModel;
    std::vector<Transform> mObjectTransforms;
    Graphics::Color4 mObjectColor;
    Math::Plane mFloorPlane;
    std::array<std::unique_ptr<Wall>, 6> mWalls;
};

} //Main 