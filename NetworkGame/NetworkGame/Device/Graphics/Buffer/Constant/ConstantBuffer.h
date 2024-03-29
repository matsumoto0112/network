#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <functional>
#include <unordered_map>
#include "Device/Graphics/DirectX11GraphicsDevice.h"
#include "Device/Graphics/Shader/ShaderInputType.h"
#include "Utility/Debug.h"

namespace Graphics {

/**
* @class ConstantBuffer
* @brief コンスタントバッファ
*/
template <class T>
class ConstantBuffer {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @param inputType どのシェーダに値を設定するか
    * @param slotNum シェーダのどのスロットに値を設定するか
    */
    ConstantBuffer(DirectX11GraphicsDevice& graphicsDevice, ShaderInputType inputType, UINT slotNumber);
    /**
    * @brief デストラクタ
    */
    virtual ~ConstantBuffer();
    /**
    * @brief 値の設定
    * @param data 設定する値
    */
    void setBuffer(T data);
    /**
    * @brief バッファの値を転送する
    */
    void sendBuffer();
    /**
    * @brief 現在のコンスタントバッファの値を取得
    */
    T getData() { return mData; }

    void clear();
private:
    /**
    * @brief バッファの転送時に使用する関数の作成
    * @param inputType どのシェーダに値を設定するか
    * @param slotNum シェーダのどのスロットに値を設定するか
    */
    std::function<void(void)> createSendBufferFunction(ShaderInputType inputType, UINT slotNumber);
private:
    DirectX11GraphicsDevice& mGraphicsDevice; //!< DirectX11用グラフィックデバイス
    T mData; //!< 現在のコンスタントバッファの値
    Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer; //!< コンスタントバッファ
    std::function<void(void)> mSendBufferFunction; //!< バッファの転送時に使用する関数
};
} //Graphics 

template<class T>
Graphics::ConstantBuffer<T>::ConstantBuffer(DirectX11GraphicsDevice& graphicsDevice,
    ShaderInputType inputType, UINT slotNumber)
    :mGraphicsDevice(graphicsDevice) {
    //バッファの作成
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = sizeof(T);
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    HRESULT hr = mGraphicsDevice.getDevice()->CreateBuffer(&desc, nullptr, &mConstantBuffer);
    //作成に失敗したらウィンドウ表示
    if (FAILED(hr)) {
        MY_ASSERTION(false, "コンスタントバッファ作成失敗");
        return;
    }
    mSendBufferFunction = createSendBufferFunction(inputType, slotNumber);
}

template<class T>
inline Graphics::ConstantBuffer<T>::~ConstantBuffer() {}

template<class T>
inline void Graphics::ConstantBuffer<T>::setBuffer(T data) {
    mData = data;
}

template<class T>
inline void Graphics::ConstantBuffer<T>::sendBuffer() {
    mGraphicsDevice.getContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr,
        &mData, 0, 0);
    mSendBufferFunction();
}

template<class T>
inline void Graphics::ConstantBuffer<T>::clear() {
    mData = T();
    mGraphicsDevice.getContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr,
        &mData, 0, 0);
    mSendBufferFunction();
}

template<class T>
inline std::function<void(void)> Graphics::ConstantBuffer<T>::createSendBufferFunction(ShaderInputType inputType, UINT slotNumber) {
    //inputTypeに応じた関数作成
    //頂点、ピクセルシェーダのどこに転送するか
    switch (inputType) {
    case ShaderInputType::Vertex:
        return [&, slotNumber]()->void {mGraphicsDevice.getContext()->VSSetConstantBuffers(slotNumber, 1, mConstantBuffer.GetAddressOf()); };
    case ShaderInputType::Pixel:
        return [&, slotNumber]()->void {mGraphicsDevice.getContext()->PSSetConstantBuffers(slotNumber, 1, mConstantBuffer.GetAddressOf()); };
    case ShaderInputType::VertexAndPixel:
        return [&, slotNumber]()->void {
            mGraphicsDevice.getContext()->VSSetConstantBuffers(slotNumber, 1, mConstantBuffer.GetAddressOf());
            mGraphicsDevice.getContext()->PSSetConstantBuffers(slotNumber, 1, mConstantBuffer.GetAddressOf());
        };
    default:
        MY_ASSERTION(false, "未定義のShaderInputTypeが選択されました。");
        return NULL;
        break;
    }
}

