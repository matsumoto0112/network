#include "Quad2D.h"
#include "Device/Graphics/Primitive/PrimitiveType.h"
#include "Device/Graphics/Primitive/PrimitiveDataStorage.h"

namespace Graphics {

Quad2D::Quad2D(GraphicsDeviceManager& graphicsDevice, const Transform2D& transform)
    :Primitive2D(PrimitiveType::Quad2D, graphicsDevice, transform) {}

Quad2D::Quad2D(GraphicsDeviceManager& graphicsDevice, const Math::AABB2D& aabb)
    : Primitive2D(PrimitiveType::Quad2D, graphicsDevice, Transform2D(aabb.position, aabb.size, 0.0f)) {}

Quad2D::~Quad2D() {}

} //Graphics 
