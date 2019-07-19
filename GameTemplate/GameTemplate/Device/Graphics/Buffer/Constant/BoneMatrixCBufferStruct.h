#pragma once
#include "Utility/Math/Matrix4x4.h"
#include "Define/Render/Animation.h"

namespace Graphics {

struct BoneMatrixCBufferStruct {
    Math::Matrix4x4 bone[Define::Animation::BONE_MAX];
};

} //Graphics 