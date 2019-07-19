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

class Stage {
public:
    Stage();
    ~Stage();
    void update(float delta);
    void draw();
private:
    std::unique_ptr<Graphics::Model> mFloor;
    Transform mFloorTransform;
    std::unique_ptr<Graphics::Model> mObjectModel;
    std::vector<Transform> mObjectTransforms;
    Graphics::Color4 mObjectColor;
    Math::Plane mFloorPlane;
};

} //Main 