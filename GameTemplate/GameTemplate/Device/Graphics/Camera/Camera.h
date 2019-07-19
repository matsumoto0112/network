#pragma once

#include <memory>
#include <vector>
#include "Utility/Transform.h"
#include "Device/Graphics/Shader/PostEffect.h"

namespace Graphics {

class GraphicsDeviceManager;
class RenderTarget;
class Quad2D;

/**
* @class Camera
* @brief カメラ抽象クラス
*/
class Camera {
public:
    /**
    * @brief コンストラクタ
    */
    Camera(GraphicsDeviceManager& graphicsDevice, std::unique_ptr<RenderTarget> renderTarget);
    /**
    * @brief 仮想デストラクタ
    */
    virtual ~Camera() = default;
    /**
    * @brief 行列の転送
    */
    virtual void setMatrix() = 0;
    /**
    * @brief このカメラに描画対象を変更する
    * @details 同時に複数のカメラをアクティブにすることはできない。常に最新の一つがアクティブになる
    */
    void setActiveRenderingCamera();
    /**
    * @brief アクティブ状態の変更
    * @param activeFlag 設定する状態
    */
    void setActive(bool activeFlag);

    /**
    * @brief アクティブ状態の取得
    */
    bool isActive() const { return mIsActive; }
    /**
    * @brief ポストエフェクトの追加
    * @param effect 追加するエフェクト
    */
    void addPostEffect(std::unique_ptr<PostEffect> effect);
    /**
    * @brief ポストエフェクト開始
    */
    void postEffect();
    /**
    * @brief ポストエフェクトリストのクリア
    */
    void clearPostEffect();

    /**
    * @brief カメラの描画結果をシェーダーに転送する
    * @param slotNum 転送する先のテクスチャ番号
    */
    void setShaderResource(int slotNum);

    void clearRenderTarget();
protected:
    GraphicsDeviceManager& mGraphicsDevice; //!< グラフィックデバイス
    std::unique_ptr<RenderTarget> mRenderTarget; //!< 描画出力先
    bool mIsActive; //!< アクティブ状態
    std::vector<std::unique_ptr<PostEffect>> mEffects; //!< ポストエフェクトリスト
    RenderTarget* mLastRendered; //!< 最後に描画したターゲット
    std::unique_ptr<Quad2D> mQuad; //!< 描画に使用する矩形
};

} //Graphics 