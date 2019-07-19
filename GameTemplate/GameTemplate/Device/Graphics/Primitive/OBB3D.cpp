#include "OBB3D.h"

namespace Graphics {

OBB3D::OBB3D(GraphicsDeviceManager& graphicsDevice, const Math::OBB3D& obb)
    :PrimitiveBase(PrimitiveType::OBB3D, graphicsDevice,
        Transform(obb.mPosition,
            Math::Quaternion(),
            Math::Vector3(obb.mLength[0] * 2.0f, obb.mLength[1] * 2.0f, obb.mLength[2] * 2.0f))),
    mOBB(obb) {}

OBB3D::~OBB3D() {}


} //Graphics 