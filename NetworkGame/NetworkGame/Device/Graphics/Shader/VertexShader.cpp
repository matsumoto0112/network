#include "VertexShader.h"
#include "Define/FileExtension.h"
#include "Define/Path.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Utility/ByteReader.h"
#include "Utility/Debug.h"

namespace Graphics {

VertexShader::VertexShader(GraphicsDeviceManager& graphicsDevice,
    const std::string& name)
    :ShaderBase(graphicsDevice), mShaderData(std::make_unique<VertexShaderData>()) {
    create(name);
}

VertexShader::~VertexShader() {}

void VertexShader::create(const std::string& name) {
    Microsoft::WRL::ComPtr<ID3D11Device> device = mGraphicsDevice.getDevice();
    //ファイルパスの作成
    const std::string filepath = Define::Path::getInstance().shader() + name + Define::FileExtensionToStringConverter::convert(Define::FileExtension::CSO);
    //シェーダファイルの読み込み
    std::vector<BYTE> shaderData = mByteReader->read(filepath);
    const UINT shaderSize = shaderData.size();

    unsigned char *pInStruct = nullptr;
    for (unsigned long i = 0L; i < shaderSize - 4; i++) {
        if (memcmp(&shaderData[i], "ISGN", 4) == NULL) {
            pInStruct = &shaderData[i];
            break;
        }
    }
    if (pInStruct == nullptr) {
        return;
    }

    //変数の数
    int cntVariable = pInStruct[8];
    std::vector<std::string>semanticsName(cntVariable);
    std::vector<UINT> semanticsIndex(cntVariable);
    std::vector<DXGI_FORMAT> format(cntVariable);
    unsigned char* str = &pInStruct[16];
    for (int i = 0; i < cntVariable; i++) {
        semanticsName[i] = std::string((char*)(str[i * 24] + pInStruct + 8));
        semanticsIndex[i] = str[i * 24 + 4];
        //ベクトルの次元数
        const char dimension = str[i * 24 + 20];
        //型の種類
        const char variant = str[i * 24 + 12];
        switch (dimension) {
            //四次元
        case '\x0f':
            switch (variant) {
            case D3D10_REGISTER_COMPONENT_FLOAT32:
                format[i] = DXGI_FORMAT_R32G32B32A32_FLOAT;
                break;
            default:
                format[i] = DXGI_FORMAT_UNKNOWN;
                break;
            }
            break;
            //三次元
        case '\x07':
            switch (variant) {
            case D3D10_REGISTER_COMPONENT_FLOAT32:
                format[i] = DXGI_FORMAT_R32G32B32_FLOAT;
                break;
            default:
                break;
            }
            break;
            //二次元
        case '\x03':
            switch (variant) {
            case D3D10_REGISTER_COMPONENT_FLOAT32:
                format[i] = DXGI_FORMAT_R32G32_FLOAT;
                break;
            default:
                format[i] = DXGI_FORMAT_UNKNOWN;
                break;
            }
            break;
            //一次元
        case '\x01':
            break;
        default:
            break;
        }
    }

    std::vector<D3D11_INPUT_ELEMENT_DESC> descs(cntVariable);
    for (int i = 0; i < cntVariable; i++) {
        descs[i] = {
            semanticsName[i].c_str(),
            semanticsIndex[i],
            format[i],
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0 };
    }

    //シェーダファイル作成
    HRESULT hr = device->CreateVertexShader(shaderData.data(), shaderSize, nullptr, &mShaderData->mVertexShader);
    MY_ASSERTION(SUCCEEDED(hr), "VertexShader作成失敗");
    //hr = device->CreateInputLayout(elementDescs.data(), elementDescs.size(),
    //    shaderData.data(), shaderSize, &mShaderData->mInputLayout);
    hr = device->CreateInputLayout(descs.data(), descs.size(),
        shaderData.data(), shaderSize, &mShaderData->mInputLayout);

    MY_ASSERTION(SUCCEEDED(hr), "InputLayout作成失敗");
}

void VertexShader::set() {
    mGraphicsDevice.getContext()->VSSetShader(mShaderData->mVertexShader.Get(), nullptr, 0);
    mGraphicsDevice.getContext()->IASetInputLayout(mShaderData->mInputLayout.Get());
}

} //Graphics 
