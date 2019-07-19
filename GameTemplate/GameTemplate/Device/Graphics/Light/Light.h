#pragma once
#include "Device/Graphics/Color4.h"
#include <functional>

namespace Graphics {
class GraphicsDeviceManager;
struct PointLightCBufferStruct;

/**
* @class Light
* @brief ライト基底クラス
* @tparam T バッファに転送する構造体
*/
template <class T>
class Light {
    using SetBufferFunc = std::function<void(T*)>;
public:
    /**
    * @brief コンストラクタ
    * @param color ライトの色
    * @param func バッファに転送する際に使用する関数
    */
    Light(const Color4& color, SetBufferFunc func);
    /**
    * @brief デストラクタ
    */
    virtual ~Light() = default;
    /**
    * @brief アクティブフラグを変更する
    */
    void setActive(bool activeFlag) { mIsActive = activeFlag; }
    /**
    * @brief アクティブ状態か
    */
    bool isActive() const { return mIsActive; }
    /**
    * @brief 色の設定
    */
    void setColor(const Color4& color) { mColor = color; }
    /**
    * @brief 色の取得
    */
    const Color4& getColor() const { return mColor; }
    /**
    * @brief バッファにライトのデータを転送する
    */
    void setParamToBuffer(T* buffer);
protected:
    Color4 mColor; //!< 色
    bool mIsActive; //!< アクティブ状態か
    SetBufferFunc mFunc; //!< バッファにデータを転送する際の関数
};

template<class T>
Light<T>::Light(const Color4& color, SetBufferFunc func)
    :mColor(color), mIsActive(true), mFunc(func) {}

template<class T>
inline void Light<T>::setParamToBuffer(T* buffer) {
    mFunc(buffer);
}

} //Graphics 