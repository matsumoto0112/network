#pragma once
#include "Device/Graphics/Camera/PerspectiveCamera.h"

namespace Graphics {

/**
* @class FPSCamera
* @brief FPS用カメラ
*/
class FPSCamera :public PerspectiveCamera {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @param info パースペクティブカメラ初期設定
    * @param renderTarget 描画出力先
    */
    FPSCamera(GraphicsDeviceManager& graphicsDevice,
        const PerspectiveCameraInfo& info,
        std::unique_ptr<RenderTarget> renderTarget);
    /**
    * @brief デストラクタ
    */
    virtual ~FPSCamera();
    /**
    * @brief 移動量と回転からカメラの座標と向きを計算する
    * @param movement 移動量
    * @param x 水平方向の回転量(deg)
    * @param y 垂直方向の回転量(deg)
    */
    void calculatePositionAndRotation(const Math::Vector3& movement, float x, float y);
private:
};

} //Graphics 