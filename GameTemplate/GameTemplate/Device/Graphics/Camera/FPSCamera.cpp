#include "FPSCamera.h"
#include "Device/Graphics/Render/RenderTarget.h"

namespace {
float getHAngle(const Math::Vector3& eye, const Math::Vector3& target) {
    // �����_�ւ̌����x�N�g�������߂�
    Math::Vector3 vDir = target - eye;

    // HAngle(XZ���ʂł̊p�x)�����߂�
    float deg = Math::MathUtility::atan2(-vDir.z, vDir.x);

    float __ADJ = 90.0f; // �����p�x(Z��������ɉ�]����)
    deg += __ADJ;

    // -180�`180�Ɋۂ߂�
    if (deg > 180.0f) { deg -= 360.0f; }
    if (deg < -180.0f) { deg += 360.0f; }

    return deg;
}

float getVAngle(const Math::Vector3& eye, const Math::Vector3& target) {
    // �����_�ւ̌����x�N�g�������߂�
    Math::Vector3 vDir = target - eye;

    float fFront;
    Math::Vector3 _vFront = vDir;
    _vFront.y = 0; // XZ���ʂł̋����Ȃ̂�Y�͂���Ȃ�
    fFront = _vFront.length();

    // Y����XZ���ʂ̑O�������Ƃ̊p�x�����߂�
    float deg = Math::MathUtility::atan2(-vDir.y, fFront);

    // ���͈͂�-90�`90
    //if (deg > 90.0f) { deg = 180.0f - deg; }
    //if (deg < -90.0f) { deg = -180.0f - deg; }
    deg = Math::MathUtility::clamp(deg, -89.9f, 89.9f);

    return deg;
}
}


namespace Graphics {

FPSCamera::FPSCamera(GraphicsDeviceManager& graphicsDevice,
    const PerspectiveCameraInfo& info,
    std::unique_ptr<RenderTarget> renderTarget)
    :PerspectiveCamera(graphicsDevice, info, std::move(renderTarget)) {}

FPSCamera::~FPSCamera() {}

void FPSCamera::calculatePositionAndRotation(const Math::Vector3& movement, float x, float y) {
    Math::Vector3 move = movement;
    float h = getHAngle(mCameraPosition, mCameraLookAt) - x;
    float v = getVAngle(mCameraPosition, mCameraLookAt) + y;
    v = Math::MathUtility::clamp(v, -45.0f, 20.0f);

    Math::Matrix4x4 mat = Math::Matrix4x4::createRotation(Math::Vector3(v, h, 0));
    move.y = 0.0f;
    move *= mat;
    move.y = 0.0f;
    mCameraPosition += move;

    mCameraLookAt = Vec3::zero();
    Math::Vector3 dir(0, 0, 1.0f);
    dir *= mat;
    mCameraLookAt = mCameraPosition + dir;
    setCameraView(mCameraPosition, mCameraLookAt, mCameraUpVector);
}

} //Graphics 
