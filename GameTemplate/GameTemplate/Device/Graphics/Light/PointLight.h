#pragma once

#include "Device/Graphics/Light/Light.h"
#include "Utility/Math/Vector3.h"
#include "Device/Graphics/Color4.h"
#include "Device/Graphics/Light/Attenuation.h"

namespace Graphics {

struct PointLightCBufferStruct;

/**
* @struct PointLightParam
* @brief ポイントライトパラメータ
*/
struct PointLightParam {
    Color4 color; //!< 色
    Math::Vector3 pos; //!< 座標
    Attenuation attenuation; //!< 減衰パラメータ
};

/**
* @class PointLight
* @brief ポイントライトクラス
*/
class PointLight final :public Light<PointLightCBufferStruct> {
public:
    /**
    * @brief コンストラクタ
    * @param param 作成するライトのパラメータ
    */
    PointLight(const PointLightParam& param);
    /**
    * @brief デストラクタ
    */
    ~PointLight();
    /**
    * @brief 座標の設定
    */
    void setPosition(const Math::Vector3& position) { mPosition = position; }
    /**
    * @brief 座標の取得
    */
    const Math::Vector3& getPosition() const { return mPosition; }
    /**
    * @brief 減衰パラメータの設定
    */
    void setAttenuation(const Attenuation& attr) { mAttenuation = attr; }
    /**
    * @brief 減衰パラメータの取得
    */
    const Attenuation& getAttenuation() const { return mAttenuation; }
private:
    /**
    * @brief バッファにデータを設定する
    * @param buffer 設定するバッファ
    */
    void setBuffer(PointLightCBufferStruct* buffer);
private:
    Math::Vector3 mPosition; //!< ライトの座標
    Attenuation mAttenuation; //!< 減衰パラメータ
};

} //Graphics 