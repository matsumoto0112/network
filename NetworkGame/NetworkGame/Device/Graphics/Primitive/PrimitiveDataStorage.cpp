#include "PrimitiveDataStorage.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Buffer/VertexAndIndexBuffer.h"
#include"Device/Graphics/Vertex/Vertex.h"
#include "Utility/Math/MathUtility.h"
#include "Utility/Debug.h"
#include "Define/Render/Primitive.h"

namespace {

std::vector<Graphics::TextureVertex> quad2DVertices() {
    return
    {
        { 0.0f,0.0f,0.0f,1.0f,0.0f,0.0f },
        { 1.0f,0.0f,0.0f,1.0f,1.0f,0.0f },
        { 1.0f,1.0f,0.0f,1.0f,1.0f,1.0f },
        { 0.0f,1.0f,0.0f,1.0f,0.0f,1.0f },
    };
}
std::vector<WORD> quad2DIndices() {
    return{ 0,1,2,0,2,3 };
}
std::vector<Graphics::TextureVertex> circle2DVertices(int divideNum) {
    std::vector<Graphics::TextureVertex> vert(divideNum);
    float angle = 0.0f;
    float step = 360.0f / divideNum;
    for (int i = 0; i < divideNum; i++, angle += step) {
        float cos = Math::MathUtility::cos(angle);
        float sin = Math::MathUtility::sin(angle);
        vert[i] = Graphics::TextureVertex(cos, sin, 0.0f, 1.0f,
            0.5f * cos + 0.5f, 0.5f + 0.5f * sin);

    }
    return vert;
}
std::vector<WORD> circle2DIndices(int divideNum) {
    std::vector<WORD> indices(divideNum * 2);
    for (int i = 0; i < divideNum; i++) {
        indices[i * 2] = i % divideNum;
        indices[(i * 2) + 1] = (i + 1) % divideNum;
    }
    return indices;
}

std::vector<Graphics::TextureVertex> obb3DVertices() {
    return
    {
        {-0.5f,-0.5f,-0.5f,1,0,1},
        { 0.5f,-0.5f,-0.5f,1,1,1},
        { 0.5f, 0.5f,-0.5f,1,1,0},
        {-0.5f, 0.5f,-0.5f,1,0,0},

        {-0.5f,-0.5f,0.5f,1,0,1},
        { 0.5f,-0.5f,0.5f,1,1,1},
        { 0.5f, 0.5f,0.5f,1,1,0},
        {-0.5f, 0.5f,0.5f,1,0,0}
    };
}

std::vector<WORD> obb3DIndices() {
    return {
        0,1,
        1,2,
        2,3,
        3,0,
        4,5,
        5,6,
        6,7,
        7,4,
        0,4,
        1,5,
        2,6,
        3,7 
    };
}
}

namespace Graphics {

PrimitiveDataStorage::PrimitiveDataStorage(GraphicsDeviceManager& graphicsDevice)
    :mGraphicsDevice(graphicsDevice) {
    addPrimitiveData(PrimitiveType::Quad2D, quad2DVertices(), quad2DIndices(), PrimitiveTopology::TriangleList);
    addPrimitiveData(PrimitiveType::Circle2D, circle2DVertices(Define::Primitive::CIRCLE_DIVIDE_NUM),
        circle2DIndices(Define::Primitive::CIRCLE_DIVIDE_NUM), PrimitiveTopology::LineList);
    addPrimitiveData(PrimitiveType::OBB3D, obb3DVertices(), obb3DIndices(), PrimitiveTopology::LineList);
}

PrimitiveDataStorage::~PrimitiveDataStorage() {
    mVIBuffers.clear();
}

VertexAndIndexBuffer* PrimitiveDataStorage::addPrimitiveData(PrimitiveType type, const std::vector<TextureVertex>& vertices, const std::vector<WORD>& indices, PrimitiveTopology topology) {
    MY_ASSERTION(mVIBuffers.find(type) == mVIBuffers.end(), "ìoò^çœÇ›ÇÃÉvÉäÉ~ÉeÉBÉuÇçƒìoò^ÇµÇÊÇ§Ç∆ÇµÇ‹ÇµÇΩ");
    auto emplaceResult = mVIBuffers.emplace(type, std::make_unique<VertexAndIndexBuffer>(mGraphicsDevice, vertices, indices, topology));
    return emplaceResult.first->second.get();
}

void PrimitiveDataStorage::drawCall(PrimitiveType type) const {
    MY_ASSERTION(mVIBuffers.find(type) != mVIBuffers.end(), "ñ¢ìoò^ÇÃÉvÉäÉ~ÉeÉBÉuÇÃÉhÉçÅ[ÉRÅ[ÉãÇ™åƒÇŒÇÍÇ‹ÇµÇΩ");
    mVIBuffers.at(type)->render();
}

VertexAndIndexBuffer* PrimitiveDataStorage::getBuffer(PrimitiveType type) const {
    MY_ASSERTION(mVIBuffers.find(type) != mVIBuffers.end(), "ìoò^çœÇ›ÇÃÉvÉäÉ~ÉeÉBÉuÇçƒìoò^ÇµÇÊÇ§Ç∆ÇµÇ‹ÇµÇΩ");
    return mVIBuffers.find(type)->second.get();
}

} //Graphics 
