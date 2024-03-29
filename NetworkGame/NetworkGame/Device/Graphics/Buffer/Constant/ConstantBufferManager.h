#pragma once

#include "Utility/Math/Matrix4x4.h"
#include "Utility/Math/Rect.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferParameterType.h"
#include "Device/Graphics/Buffer/Constant/LightingCBufferStruct.h"
#include "Device/Graphics/Buffer/Constant/BoneMatrixCBufferStruct.h"
#include "Device/Graphics/Color4.h"
#include "Device/Graphics/Buffer/Constant/ConstantBuffer.h"

namespace Graphics {

class DirectX11GraphicsDevice;
template <class T>
class ConstantBufferTypeManager;
struct MVPMatrixCBufferStruct;
struct UVInfoCBufferStruct;
struct ColorCBufferStruct;
struct MaterialCBufferStruct;
struct CameraNumCBufferStruct;

/**
* @class ConstantBufferManager
* @brief コンスタントバッファ管理者
*/
class ConstantBufferManager {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    */
    ConstantBufferManager(DirectX11GraphicsDevice& graphicsDevice);
    /**
    * @brief デストラクタ
    */
    ~ConstantBufferManager();
    /**
    * @brief データの転送
    */
    void send();
    /**
    * @brief 行列の設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setMatrix(ConstantBufferParameterType type, const Math::Matrix4x4& value);
    /**
    * @brief Floatの設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setFloat(ConstantBufferParameterType type, float value);
    /**
    * @brief 色の設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setColor(ConstantBufferParameterType type, const Color4& value);
    /**
    * @brief Intの設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setInt(ConstantBufferParameterType type, int value);
    /**
    * @brief Boolの設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setBool(ConstantBufferParameterType type, bool value);
    /**
    * @brief 矩形の設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setRect(ConstantBufferParameterType type, const Math::Rect& value);
    /**
    * @brief 構造体の設定
    * @tparam T 転送する構造体
    * @param type 転送先
    */
    template <class T>
    void setStruct(const T& value);
    void clearBuffer();
private:
    /**
    * @brief 初期設定
    */
    void setup();
    DirectX11GraphicsDevice& mDevice; //!< DirectX11用グラフィックデバイス

    std::unique_ptr<ConstantBuffer<MVPMatrixCBufferStruct>> mMVPCBuffer; //!< MVP行列用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<UVInfoCBufferStruct>> mUVCBuffer; //!< UV用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<ColorCBufferStruct>> mColorCBuffer; //!< 色用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<MaterialCBufferStruct>> mMaterial; //!< マテリアル用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<CameraNumCBufferStruct>> mCameraCBuffer; //!< カメラ用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<LightingCBufferStruct>> mLightingCBuffer; //!< ライティング用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<BoneMatrixCBufferStruct>> mBoneMatrixCBuffer; //!< ボーン行列用コンスタントバッファ

    std::unique_ptr<ConstantBufferTypeManager<Math::Matrix4x4>> mMatrixBufferManager; //!< 行列用バッファ転送管理者
    std::unique_ptr<ConstantBufferTypeManager<float>> mFloatBufferManager; //!< Float用バッファ転送管理者
    std::unique_ptr<ConstantBufferTypeManager<Math::Rect>> mRectBufferManager; //!< 矩形用バッファ転送管理者
    std::unique_ptr<ConstantBufferTypeManager<Color4>> mColorBufferManager; //!< 色用バッファ転送管理者
    std::unique_ptr<ConstantBufferTypeManager<int>> mIntBufferManager; //!< 整数値用バッファ転送管理者
};

template<>
inline void ConstantBufferManager::setStruct(const LightingCBufferStruct& value) {
    mLightingCBuffer->setBuffer(value);
}

template<>
inline void ConstantBufferManager::setStruct(const BoneMatrixCBufferStruct& value) {
    mBoneMatrixCBuffer->setBuffer(value);
    mBoneMatrixCBuffer->sendBuffer();
}

template<class T>
inline void ConstantBufferManager::setStruct(const T& value) {
    static_assert(false);
}

} //Graphics 