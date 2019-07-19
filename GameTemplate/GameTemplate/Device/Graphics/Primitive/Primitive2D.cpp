#include "Primitive2D.h"
#include "Device/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Primitive/PrimitiveDataStorage.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"

namespace Graphics {

Primitive2D::Primitive2D(PrimitiveType type, 
    GraphicsDeviceManager& graphicsDevice,
    const Transform2D& transform)
    : mType(type), mGraphicsDevice(graphicsDevice),mTransform(transform) {
    //バッファを持ってくる
    mBuffer = mGraphicsDevice.getPrimtiveStorage().getBuffer(type);
}

Primitive2D::~Primitive2D() {}

void Primitive2D::render() {
    ConstantBufferManager& cmanager = mGraphicsDevice.getConstantBufferManager();
    mGraphicsDevice.getConstantBufferManager().setMatrix(ConstantBufferParameterType::World, Math::Matrix4x4::transposition(mTransform.createSRTMatrix()));
    mBuffer->render();
}

} //Graphics 