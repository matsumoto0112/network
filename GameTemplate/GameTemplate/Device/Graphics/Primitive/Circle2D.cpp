#include "Circle2D.h"
#include "Device/Graphics/Primitive/PrimitiveType.h"

namespace Graphics {

Circle2D::Circle2D(GraphicsDeviceManager& graphicsDevice, const Transform2D& transform)
    :Primitive2D(PrimitiveType::Circle2D, graphicsDevice, transform) {}

Circle2D::Circle2D(GraphicsDeviceManager& graphicsDevice, const Math::Circle2D& circle)
    : Primitive2D(PrimitiveType::Circle2D, graphicsDevice,
        Transform2D(circle.center, Math::Vector2(circle.radius, circle.radius), 0.0f)) {}

Circle2D::~Circle2D() {}

} //Graphics 
