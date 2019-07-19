#include "OrthographicCamera.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/Render/RenderTarget.h"
#include "Device/Graphics/Primitive/Quad2D.h"


namespace Graphics {

OrthographicCamera::OrthographicCamera(GraphicsDeviceManager& graphicsDevice,
    const Math::Vector2& screenSize, std::unique_ptr<RenderTarget> renderTarget)
    :Camera(graphicsDevice, std::move(renderTarget)), mScreenSize(screenSize) {
    setOrthographicMatrix();
}

OrthographicCamera::~OrthographicCamera() {}

void OrthographicCamera::setMatrix() {
    mView.setupTransform(-mPosition);
    mGraphicsDevice.getConstantBufferManager().
        setMatrix(ConstantBufferParameterType::View,
            Math::Matrix4x4::transposition(mView));
    mGraphicsDevice.getConstantBufferManager().
        setMatrix(ConstantBufferParameterType::Projection,
            Math::Matrix4x4::transposition(mProj));
}

void OrthographicCamera::setScreenSize(const Math::Vector2& screenSize) {
    mScreenSize = screenSize;
}

const Math::Vector2& OrthographicCamera::getScreenSize() const {
    return mScreenSize;
}

void OrthographicCamera::setOrthographicMatrix() {
    mProj.setUpOrthographic(mScreenSize);
}


} //Graphics 
