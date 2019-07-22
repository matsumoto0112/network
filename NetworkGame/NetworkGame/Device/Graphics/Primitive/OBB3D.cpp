#include "OBB3D.h"

namespace Graphics {

OBB3D::OBB3D(GraphicsDeviceManager& graphicsDevice, const Math::OBB3D& obb)
    :PrimitiveBase(PrimitiveType::OBB3D, graphicsDevice,
        Transform(obb.mPosition,
            Math::Quaternion(),
            Math::Vector3(obb.mLength.x * 2.0f, obb.mLength.y * 2.0f, obb.mLength.z * 2.0f))),
    mOBB(obb) {}

OBB3D::~OBB3D() {}


} //Graphics 