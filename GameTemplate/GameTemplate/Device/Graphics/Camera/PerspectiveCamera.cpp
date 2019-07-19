#include "PerspectiveCamera.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Render/RenderTarget.h"
#include "Device/Graphics/Primitive/Quad2D.h"
#include <iostream>
#undef near
#undef far


namespace Graphics {

PerspectiveCamera::PerspectiveCamera(GraphicsDeviceManager& graphicsDevice,
    const PerspectiveCameraInfo& info,
    std::unique_ptr<RenderTarget> renderTarget)
    : Camera(graphicsDevice, std::move(renderTarget)) {
    setCameraView(info.eye, info.at, info.up);
    setProjection(info.fov, info.screenSize, info.near, info.far);
    mLength = (mCameraLookAt - mCameraPosition).length();
}

PerspectiveCamera::~PerspectiveCamera() {}

const Math::Matrix4x4& PerspectiveCamera::getView() const {
    return mView;
}

const Math::Matrix4x4& PerspectiveCamera::getProjection() const {
    return mProjection;
}

void PerspectiveCamera::setPosition(const Vec3& position, bool keepLookAt) {
    if (keepLookAt) {
        Vec3 diff = position - mCameraPosition;
        mCameraPosition = position;
        mCameraLookAt += diff;
    }
    else {
        mCameraPosition = position;
        mLength = (mCameraPosition - mCameraLookAt).length();
    }
    setCameraView(mCameraPosition, mCameraLookAt, mCameraUpVector);
}

const Math::Vector3& PerspectiveCamera::getPosition() const {
    return mCameraPosition;
}

void PerspectiveCamera::setLookAt(const Vec3& at) {
    mCameraLookAt = at;
    mLength = (mCameraPosition - mCameraLookAt).length();
    setCameraView(mCameraPosition, mCameraLookAt, mCameraUpVector);
}

const Math::Vector3& PerspectiveCamera::getLookAt() const {
    return mCameraLookAt;
}

void PerspectiveCamera::setUpVector(const Vec3& up) {
    mCameraUpVector = up;
    setCameraView(mCameraPosition, mCameraLookAt, mCameraUpVector);
}

const Math::Vector3& PerspectiveCamera::getUpVector() const {
    return mCameraUpVector;
}

void PerspectiveCamera::setCameraView(const Vec3& eye, const Vec3& at, const Vec3& up) {
    mView.setUpView(eye, at, up);
    mCameraPosition = eye;
    mCameraLookAt = at;
    mCameraUpVector = up;
}

void PerspectiveCamera::setProjection(float fov, const Vec2& screen, float near, float far) {
    mProjection.setProjection(fov, screen.x, screen.y, near, far);
}

void PerspectiveCamera::setMatrix() {
    mGraphicsDevice.getConstantBufferManager().setMatrix(ConstantBufferParameterType::View,
        Math::Matrix4x4::transposition(getView()));
    mGraphicsDevice.getConstantBufferManager().setMatrix(ConstantBufferParameterType::Projection,
        Math::Matrix4x4::transposition(getProjection()));
}

} //Graphics 
