#include "ShaderBase.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Utility/ByteReader.h"

namespace Graphics {

Graphics::ShaderBase::ShaderBase(GraphicsDeviceManager& graphicsDevice)
    :mGraphicsDevice(graphicsDevice),
    mDeviceContext(graphicsDevice.getContext()),
    mByteReader(std::make_unique<Utility::ByteReader>()) {}

} //Graphics 
