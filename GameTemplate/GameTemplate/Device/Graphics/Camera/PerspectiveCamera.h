#pragma once

#include "Device/Graphics/Camera/Camera.h"
#include "Utility/Math/Vector2.h"
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Matrix4x4.h"
#include "Utility/Transform.h"

#undef near
#undef far

namespace Graphics {

/**
* @class PerspectiveCameraInfo
* @brief カメラの情報
*/
struct PerspectiveCameraInfo {
    Math::Vector3 eye; //!< カメラ座標
    Math::Vector3 at; //!< 注視点
    Math::Vector3 up; //!< 視点の上方向
    float fov; //!< 視野角（度）
    Math::Vector2 screenSize; //!< スクリーンの大きさ
    float near; //!< 最近点
    float far; //!< 最遠点
};

/**
* @class PerspectiveCamera
* @brief 透視投影カメラクラス
*/
class PerspectiveCamera : public Camera {
private:
    using Vec2 = Math::Vector2;
    using Vec3 = Math::Vector3;
    using Mat4 = Math::Matrix4x4;
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @param info カメラの情報
    * @param renderTarget 描画対象
    */
    PerspectiveCamera(GraphicsDeviceManager& graphicsDevice, const PerspectiveCameraInfo& info,
        std::unique_ptr<RenderTarget> renderTarget);
    /**
    * @brief デストラクタ
    */
    virtual ~PerspectiveCamera();
    /**
    * @brief ビュー行列の取得
    */
    const Mat4& getView() const;
    /**
    * @brief プロジェクション行列の取得
    */
    const Mat4& getProjection() const;
    /**
    * @brief カメラ座標の設定
    * @param position 設定する座標
    * @param keepLookAt 視点を座標に合わせて相対的に移動させるか
    */
    void setPosition(const Vec3& position, bool keepLookAt = false);
    /**
    * @brief カメラ座標の取得
    */
    const Vec3& getPosition() const;
    /**
    * @brief カメラの注視点の設定
    */
    void setLookAt(const Vec3& at);
    /**
    * @brief カメラの注視点の取得
    */
    const Vec3& getLookAt() const;
    /**
    * @brief カメラの上方向の設定
    */
    void setUpVector(const Vec3& up);
    /**
    * @brief カメラの上方向の取得
    */
    const Vec3& getUpVector() const;

    /**
    * @brief カメラ情報の再設定
    * @param eye カメラ座標
    * @param at 注視点
    * @param up 視点の上方向
    */
    void setCameraView(const Vec3& eye, const Vec3& at, const Vec3& up);
    /**
    * @brief プロジェクション行列の再設定
    * @param fov 視野角（度）
    * @param screen スクリーンの大きさ
    * @param near 最近点
    * @param far 最遠点
    */
    void setProjection(float fov, const Vec2& screen, float near, float far);
    /**
    * @brief 行列をコンスタントバッファに転送する
    */
    virtual void setMatrix() override;
protected:
    Vec3 mCameraPosition; //!< カメラ座標
    Vec3 mCameraLookAt; //!< カメラ注視点
    Vec3 mCameraUpVector; //!< カメラ上方向
    Mat4 mView; //!< ビュー行列
    Mat4 mProjection; //!< プロジェクション行列
    float mLength; //!< カメラの座標から視点までの距離
};

} //Graphics 