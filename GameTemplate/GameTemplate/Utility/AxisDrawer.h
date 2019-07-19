#pragma once

#include <array>
#include <memory>
#include "Utility/Math/Matrix4x4.h"
#include "Device/Graphics/Color4.h"

namespace Graphics {
class VertexAndIndexBuffer;
class Effect;
} //Graphics 

namespace Utility {

class AxisDrawer {
public:
    AxisDrawer();
    ~AxisDrawer();
    void draw();
private:
    std::array<std::pair<std::unique_ptr<Graphics::VertexAndIndexBuffer>, Graphics::Color4>, 3> mAxisBuffer;
    std::shared_ptr<Graphics::Effect> mEffect;
    Math::Matrix4x4 mWorldMatrix;
};

} //Utility 