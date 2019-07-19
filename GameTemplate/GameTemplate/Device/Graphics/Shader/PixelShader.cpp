#include "PixelShader.h"
#include "Define/FileExtension.h"
#include "Define/Path.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Utility/ByteReader.h"


namespace Graphics {

PixelShader::PixelShader(GraphicsDeviceManager& graphicsDevice, const std::string& filename)
    : ShaderBase(graphicsDevice), mShaderData(std::make_unique<PixelShaderData>()) {
    create(filename);
}

PixelShader::~PixelShader() {}

void PixelShader::create(const std::string& name) {
    //ファイルパスの作成
    const std::string filename = Define::Path::getInstance().shader() + name + Define::FileExtensionToStringConverter::convert(Define::FileExtension::CSO);
    //シェーダファイルの読み込み
    std::vector<BYTE> byteData = mByteReader->read(filename);
    //シェーダファイル作成
    mGraphicsDevice.getDevice()->CreatePixelShader(byteData.data(), byteData.size(), nullptr, &mShaderData->mPixelShader);
}

void PixelShader::set() {
    mGraphicsDevice.getContext()->PSSetShader(mShaderData->mPixelShader.Get(), nullptr, 0);
}

} //Graphics 
