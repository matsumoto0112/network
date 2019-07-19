#pragma once

#include "Utility/Math/Primitive2D.h"
#include "Device/Graphics/Primitive/Primitive2D.h"

namespace Graphics {

class Quad2D : public Primitive2D {
public:
    Quad2D(GraphicsDeviceManager& graphicsDevice,const Transform2D& transform);
    Quad2D(GraphicsDeviceManager& graphicsDevice, const Math::AABB2D& aabb);
    virtual ~Quad2D();
};

} //Graphics 