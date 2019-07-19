#pragma once

#include "Device/Graphics/Light/Light.h"
#include "Utility/Math/Vector3.h"

namespace Graphics {

struct DirectionalLightCBufferStruct;

/**
* @struct DirectionalLightParam
* @brief ディレクショナルライトパラメータ
*/
struct DirectionalLightParam {
    Color4 color; //!< 色
    Math::Vector3 dir; //!< 方向ベクトル
};

/**
* @class DirectionalLight
* @brief ディレクショナルライトクラス
*/
class DirectionalLight final : public Light<DirectionalLightCBufferStruct> {
public:
    /**
    * @brief コンストラクタ
    * @param param 作成するディレクショナルライトのパラメータ
    */
    DirectionalLight(const DirectionalLightParam& param);
    /**
    * @brief デストラクタ
    */
    ~DirectionalLight();
    /**
    * @brief 方向ベクトルの設定
    */
    void setDirection(const Math::Vector3& direction) { mDirection = direction; }
    /**
    * @brief 方向ベクトルの取得
    */
    const Math::Vector3& getDirection() const { return mDirection; }
private:
    /**
    * @brief バッファにデータを設定する
    * @param buffer 設定するバッファ
    */
    void setBuffer(DirectionalLightCBufferStruct* buffer);
private:
    Math::Vector3 mDirection; //!< ライトの方向ベクトル
};

} //Graphics 