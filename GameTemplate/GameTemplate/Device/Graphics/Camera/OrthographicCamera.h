#pragma once

#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Camera/Camera.h"
#include "Utility/Math/Matrix4x4.h"

namespace Graphics {

/**
* @class OrthographicCamera
* @brief 正投影カメラクラス
*/
class OrthographicCamera : public Camera {
public:
    /**
    * コンストラクタ
    * @param graphicsDevice グラフィックデバイス管理者
    * @param screenSize スクリーンの大きさ
    * @param renderTarget 描画対象
    */
    OrthographicCamera(GraphicsDeviceManager& graphicsDevice,
        const Math::Vector2& screenSize, std::unique_ptr<RenderTarget> renderTarget);
    /**
    * @brief デストラクタ
    */
    virtual ~OrthographicCamera();
    /**
    * @brief 行列の設定
    */
    virtual void setMatrix() override;
    /**
    * @brief スクリーンの大きさの設定
    * @param screenSize 設定するスクリーンサイズ
    */
    void setScreenSize(const Math::Vector2& screenSize);
    /**
    * @brief スクリーンの大きさの取得
    * @return カメラに登録されたスクリーンの大きさ
    */
    const Math::Vector2& getScreenSize() const;

    const Math::Vector3& getPosition() const { return mPosition; }
    void setPosition(const Math::Vector3& position) { mPosition = position; }
private:
    /**
    * @brief 正投影行列の設定
    */
    void setOrthographicMatrix();
private:
    Math::Vector2 mScreenSize; //!< カメラに設定されているスクリーンの大きさ
    Math::Matrix4x4 mView; //!< ビュー行列
    Math::Matrix4x4 mProj; //!< プロジェクション行列
    Math::Vector3 mPosition; //!< カメラ座標

};

} //Graphics 
