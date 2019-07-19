#include "PrimitiveBase.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Device/Graphics/Primitive/PrimitiveDataStorage.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"

namespace Graphics {

PrimitiveBase::PrimitiveBase(PrimitiveType type,
    GraphicsDeviceManager& graphicsDevice,
    const Transform& transform)
    :mType(type), mGraphicsDevice(graphicsDevice), mTransform(transform) {
    mBuffer = mGraphicsDevice.getPrimtiveStorage().getBuffer(mType);

}

PrimitiveBase::~PrimitiveBase() {}

void PrimitiveBase::render() {
    ConstantBufferManager& cmanager = mGraphicsDevice.getConstantBufferManager();
    cmanager.setMatrix(ConstantBufferParameterType::World, Math::Matrix4x4::transposition(mTransform.createSRTMatrix()));
    mBuffer->render();
}

} //Graphics 
