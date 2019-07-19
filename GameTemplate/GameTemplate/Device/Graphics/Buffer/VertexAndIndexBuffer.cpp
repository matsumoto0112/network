#include "VertexAndIndexBuffer.h"
#include "Device/Graphics/Buffer/VertexBuffer.h"
#include "Device/Graphics/Buffer/IndexBuffer.h"

#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"

namespace Graphics {

VertexAndIndexBuffer::~VertexAndIndexBuffer() {}

void VertexAndIndexBuffer::render() {
    mGraphicsDevice.getConstantBufferManager().send();
    mVertexBuffer->setData();
    mIndexBuffer->setData();
    mIndexBuffer->drawCall();
}

} //Graphics 
