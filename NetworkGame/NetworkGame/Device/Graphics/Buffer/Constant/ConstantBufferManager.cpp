#include "ConstantBufferManager.h"
#include "Utility/Debug.h"
#include "Device/Graphics/Buffer/Constant/ConstantBuffer.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferTypeManager.h"
#include "Device/Graphics/Buffer/Constant/MVPMatrixCBufferStruct.h"
#include "Device/Graphics/Buffer/Constant/UVInfoCBufferStruct.h"
#include "Device/Graphics/Buffer/Constant/ColorCBufferStruct.h"
#include "Device/Graphics/Buffer/Constant/MaterialCBufferStruct.h"
#include "Device/Graphics/Buffer/Constant/CameraNumCBufferStruct.h"

#define MY_SETBUFFER_FUNC(ValueType,StructType,buffer,Parameter) \
([&](const ValueType& value) -> void{\
StructType& s = buffer->getData();\
s.##Parameter = value;\
buffer->setBuffer(s);})

namespace Graphics {

ConstantBufferManager::ConstantBufferManager(DirectX11GraphicsDevice& graphicsDevice)
    :mDevice(graphicsDevice),
    mMatrixBufferManager(std::make_unique<ConstantBufferTypeManager<Math::Matrix4x4>>()),
    mFloatBufferManager(std::make_unique<ConstantBufferTypeManager<float>>()),
    mRectBufferManager(std::make_unique<ConstantBufferTypeManager<Math::Rect>>()),
    mColorBufferManager(std::make_unique<ConstantBufferTypeManager<Color4>>()),
    mIntBufferManager(std::make_unique<ConstantBufferTypeManager<int>>()) {
    setup();
}

ConstantBufferManager::~ConstantBufferManager() {}

void ConstantBufferManager::send() {
    mMVPCBuffer->sendBuffer();
    mUVCBuffer->sendBuffer();
    mColorCBuffer->sendBuffer();
    mMaterial->sendBuffer();
    mCameraCBuffer->sendBuffer();
    mLightingCBuffer->sendBuffer();
}

void ConstantBufferManager::setMatrix(ConstantBufferParameterType type, const Math::Matrix4x4& value) {
    mMatrixBufferManager->set(type, value);
}

void ConstantBufferManager::setFloat(ConstantBufferParameterType type, float value) {
    mFloatBufferManager->set(type, value);
}

void ConstantBufferManager::setColor(ConstantBufferParameterType type, const Color4& value) {
    mColorBufferManager->set(type, value);
}

void ConstantBufferManager::setInt(ConstantBufferParameterType type, int value) {
    mIntBufferManager->set(type, value);
}

void ConstantBufferManager::setBool(ConstantBufferParameterType type, bool value) {}

void ConstantBufferManager::setRect(ConstantBufferParameterType type, const Math::Rect& value) {
    mRectBufferManager->set(type, value);
}

void ConstantBufferManager::clearBuffer() {
    mMVPCBuffer->clear();
    mUVCBuffer->clear();
    mColorCBuffer->clear();
    mMaterial->clear();
    mCameraCBuffer->clear();
}

void ConstantBufferManager::setup() {
    mMVPCBuffer = std::make_unique<ConstantBuffer<MVPMatrixCBufferStruct>>(mDevice, ShaderInputType::VertexAndPixel, 0);

    mMatrixBufferManager->add(ConstantBufferParameterType::World,
        MY_SETBUFFER_FUNC(Math::Matrix4x4, MVPMatrixCBufferStruct, mMVPCBuffer, world));
    mMatrixBufferManager->add(ConstantBufferParameterType::View,
        MY_SETBUFFER_FUNC(Math::Matrix4x4, MVPMatrixCBufferStruct, mMVPCBuffer, view));
    mMatrixBufferManager->add(ConstantBufferParameterType::Projection,
        MY_SETBUFFER_FUNC(Math::Matrix4x4, MVPMatrixCBufferStruct, mMVPCBuffer, proj));

    mUVCBuffer = std::make_unique<ConstantBuffer<UVInfoCBufferStruct>>(mDevice, ShaderInputType::VertexAndPixel, 2);
    mRectBufferManager->add(ConstantBufferParameterType::UV,
        MY_SETBUFFER_FUNC(Math::Rect, UVInfoCBufferStruct, mUVCBuffer, uv));

    mColorCBuffer = std::make_unique<ConstantBuffer<ColorCBufferStruct>>(mDevice, ShaderInputType::VertexAndPixel, 3);
    mColorBufferManager->add(ConstantBufferParameterType::Color,
        MY_SETBUFFER_FUNC(Color4, ColorCBufferStruct, mColorCBuffer, color));

    mMaterial = std::make_unique<ConstantBuffer<MaterialCBufferStruct>>(mDevice, ShaderInputType::VertexAndPixel, 4);

    mColorBufferManager->add(ConstantBufferParameterType::Ambient,
        MY_SETBUFFER_FUNC(Color4, MaterialCBufferStruct, mMaterial, ambient));
    mColorBufferManager->add(ConstantBufferParameterType::Diffuse,
        MY_SETBUFFER_FUNC(Color4, MaterialCBufferStruct, mMaterial, diffuse));
    mColorBufferManager->add(ConstantBufferParameterType::Specular,
        MY_SETBUFFER_FUNC(Color4, MaterialCBufferStruct, mMaterial, specular));
    mFloatBufferManager->add(ConstantBufferParameterType::Shininess,
        MY_SETBUFFER_FUNC(float, MaterialCBufferStruct, mMaterial, shininess));
    mFloatBufferManager->add(ConstantBufferParameterType::Alpha,
        MY_SETBUFFER_FUNC(float, MaterialCBufferStruct, mMaterial, alpha));

    mCameraCBuffer = std::make_unique<ConstantBuffer<CameraNumCBufferStruct>>(mDevice, ShaderInputType::VertexAndPixel, 5);
    mIntBufferManager->add(ConstantBufferParameterType::CameraNum,
        MY_SETBUFFER_FUNC(int, CameraNumCBufferStruct, mCameraCBuffer, cameraNum));

    mLightingCBuffer = std::make_unique<ConstantBuffer<LightingCBufferStruct>>(mDevice,
        ShaderInputType::VertexAndPixel, 1);

    mBoneMatrixCBuffer = std::make_unique<ConstantBuffer<BoneMatrixCBufferStruct>>(mDevice,
        ShaderInputType::VertexAndPixel, 6);
}

} //Graphics 
