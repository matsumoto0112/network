#include "VertexBuffer.h"

namespace Graphics {

VertexBuffer::~VertexBuffer() {}

void VertexBuffer::setData() {
    mDevice.getContext()->IASetVertexBuffers(0, 1, 
        mData->mBuffer.GetAddressOf(), &mData->mStride, &mData->mOffset);
}

} //Graphics 