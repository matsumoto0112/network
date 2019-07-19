#pragma once

#include <d3d11.h>
#include <unordered_map>
#include <memory>
#include "Device/Graphics/Primitive/PrimitiveType.h"

namespace Graphics {

class GraphicsDeviceManager;
class VertexAndIndexBuffer;
enum class PrimitiveTopology;
struct TextureVertex;

class PrimitiveDataStorage {
public:
    PrimitiveDataStorage(GraphicsDeviceManager& graphicsDevice);
    ~PrimitiveDataStorage();
    VertexAndIndexBuffer* addPrimitiveData(PrimitiveType type,
        const std::vector<TextureVertex>& vertices, const std::vector<WORD>& indices, PrimitiveTopology topology);
    void drawCall(PrimitiveType type) const;
    VertexAndIndexBuffer* getBuffer(PrimitiveType type) const;
private:
    GraphicsDeviceManager& mGraphicsDevice;
    std::unordered_map<PrimitiveType, std::unique_ptr<VertexAndIndexBuffer>> mVIBuffers;
};

} //Graphics 
