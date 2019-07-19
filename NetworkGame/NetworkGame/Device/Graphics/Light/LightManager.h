#pragma once

#include <memory>
#include <vector>
#include "Utility/Math/Vector3.h"
#include "Device/Graphics/Color4.h"
#include "Device/Graphics/Light/Attenuation.h"
#include "Utility/Debug.h"
#include "Device/Graphics/Light/PointLight.h"
#include "Device/Graphics/Light/DirectionalLight.h"

namespace Graphics {

class GraphicsDeviceManager;

/**
* @class LightManager
* @brief ライト管理者
*/
class LightManager {
public:
    /**
    * @brief コンストラクタ
    * @param device グラフィックデバイス
    */
    LightManager(GraphicsDeviceManager& device);
    /**
    * @brief デストラクタ
    */
    virtual ~LightManager();
    /**
    * @brief ライトの追加
    * @param param ライトのパラメータ
    * @return 追加されたライトのインデックス
    */
    int addLight(const PointLightParam& param);
    /**
    * @brief ライトの追加
    * @param param ライトのパラメータ
    * @return 追加されたライトのインデックス
    */
    int addLight(const DirectionalLightParam& param);
    /**
    * @brief ライトの取得
    * @tparam T 取得したいライトの型
    * @param index ライトのインデックス
    */
    template <class T>
    T& getLight(int index);
    /**
    * @brief バッファにデータを転送する
    */
    void set();
private:
    GraphicsDeviceManager& mDevice; //!< グラフィックデバイス
    std::vector<std::unique_ptr<DirectionalLight>> mDirectionalLights; //!< ディレクショナルライトリスト
    std::vector<std::unique_ptr<PointLight>> mPointLights; //!< ポイントライトリスト
};

template<>
inline PointLight& LightManager::getLight(int id) {
    MY_ASSERTION(id < (int)mPointLights.size(),
        "インデックスが配列の範囲外です。");
    return *mPointLights[id];
}

template <>
inline DirectionalLight& LightManager::getLight(int id) {
    MY_ASSERTION(id < (int)mDirectionalLights.size(),
        "インデックスが配列の範囲外です。");
    return *mDirectionalLights[id];
}

template <class T>
inline T& LightManager::getLight(int id) {
    static_assert(false, "exist undefined light type");
}

} //Graphics 