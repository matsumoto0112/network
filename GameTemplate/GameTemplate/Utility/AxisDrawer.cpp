#include "AxisDrawer.h"
#include <vector>
#include "Device/GameDevice.h"
#include "Device/Graphics/Color4.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Device/Graphics/Shader/Effect.h"
#include "Device/Graphics/Vertex/Vertex.h"
#include "Utility/Resource/ResourceManager.h"
#include "Utility/Resource/VertexShaderResourceStorage.h"
#include "Utility/Resource/PixelShaderResourceStorage.h"

namespace Utility {

AxisDrawer::AxisDrawer() {
    std::vector<Graphics::Vertex> xaxis{
        {-1.0f,0.0f,0.0f,1.0f},
        {1.0f,0.0f,0.0f,1.0f}
    };
    std::vector<Graphics::Vertex> yaxis{
        {0.0f,-1.0f,0.0f,1.0f},
        {0.0f,1.0f,0.0f,1.0f}
    };
    std::vector<Graphics::Vertex> zaxis{
        {0.0f,0.0f,-1.0f,1.0f},
        {0.0f,0.0f,1.0f,1.0f}
    };
    std::vector<WORD> indices{ 0,1 };

    Graphics::GraphicsDeviceManager& device = Device::GameDevice::getInstance().getDirectX11Device();
    mAxisBuffer[0].first = std::make_unique<Graphics::VertexAndIndexBuffer>(device, xaxis, indices, Graphics::PrimitiveTopology::LineList);
    mAxisBuffer[0].second = Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f);

    mAxisBuffer[1].first = std::make_unique<Graphics::VertexAndIndexBuffer>(device, yaxis, indices, Graphics::PrimitiveTopology::LineList);
    mAxisBuffer[1].second = Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f);

    mAxisBuffer[2].first = std::make_unique<Graphics::VertexAndIndexBuffer>(device, zaxis, indices, Graphics::PrimitiveTopology::LineList);
    mAxisBuffer[2].second = Graphics::Color4(0.0f, 0.0f, 1.0f, 1.0f);

    Utility::ResourceManager& rsManager = Utility::ResourceManager::getInstance();
    mEffect = std::make_unique<Graphics::Effect>(
        rsManager.getVertexShader()->getResource(Define::VertexShaderType::OnlyPosition),
        rsManager.getPixelShader()->getResource(Define::PixelShaderType::OnlyPosition));

    mWorldMatrix.setupScale(Math::Vector3(100.0f, 100.0f, 100.0f));
}

AxisDrawer::~AxisDrawer() {}

void AxisDrawer::draw() {
    Graphics::ConstantBufferManager& cbManager = Device::GameDevice::getInstance().getDirectX11Device().getConstantBufferManager();
    cbManager.setMatrix(Graphics::ConstantBufferParameterType::World, Math::Matrix4x4::transposition(mWorldMatrix));
    mEffect->set();
    for (auto&& axis : mAxisBuffer) {
        cbManager.setColor(Graphics::ConstantBufferParameterType::Color, axis.second);
        axis.first->render();
    }
}

} //Utility 
