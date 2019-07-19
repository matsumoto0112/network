#pragma once

#include <map>
#include <memory>
#include "Utility/Debug.h"
#include "Device/Graphics/Camera/Camera.h"
#include "Define/Render/CameraType.h"
#include "Utility/Singleton.h"

namespace Graphics {

class Quad2D;
class Effect;

/**
* @class CameraManager
* @brief カメラ管理
*/
class CameraManager : public Utility::Singleton<CameraManager> {
public:
    /**
    * @brief デストラクタ
    */
    ~CameraManager();
    /**
    * @brief カメラの追加
    * @param type カメラの種類
    * @param camera 追加するカメラ
    * @details カメラがすでに追加されていたらエラーとなる
    */
    void addCamera(Define::CameraType type, std::unique_ptr<Camera> camera);
    /**
    * @brief レンダリングするカメラを切り替える
    * @param type 変更したいカメラの種類
    */
    void setRenderingCamera(Define::CameraType type);
    /**
    * @brief すべてのカメラの描画処理をする
    * @details カメラのisActiveがfalseの場合、描画処理を行わない
    */
    void render();
    /**
    * @brief カメラの取得
    * @tparam T 取得するカメラの型
    * @param type カメラの種類
    * @return 取得したい型に変換されたカメラ
    */
    template <class T>
    T& getCamera(Define::CameraType type);
protected:
    /**
    * @brief コンストラクタ
    */
    CameraManager();
private:
    GraphicsDeviceManager& mGraphicsDevice; //!< グラフィックデバイス
    std::map<Define::CameraType, std::unique_ptr<Camera>> mCameras; //!< カメラ
    std::unique_ptr<Quad2D> mQuad; //!< 画面と同じサイズの矩形
    std::unique_ptr<Effect> mBlendEffect; //!< カメラのレンダリング結果を合成するシェーダー
};

template<class T>
inline T& CameraManager::getCamera(Define::CameraType type) {
    MY_ASSERTION(mCameras.find(type) != mCameras.end(),
        "未登録のカメラが呼ばれました");
    Camera& camera = *mCameras[type];
    return dynamic_cast<T&>(camera);
}

} //Graphics 