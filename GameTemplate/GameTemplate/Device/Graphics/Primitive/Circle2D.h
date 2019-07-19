#pragma once

#include "Device/Graphics/Primitive/Primitive2D.h"
#include "Utility/Math/Primitive2D.h"

namespace Graphics {

class Circle2D : public Primitive2D {
public:
    Circle2D(GraphicsDeviceManager& graphicsDevice, const Transform2D& transform);
    Circle2D(GraphicsDeviceManager& graphicsDevice, const Math::Circle2D& circle);
    ~Circle2D();
};

} //Graphics 
