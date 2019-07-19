#pragma once

#include <memory>
namespace Scene {

class IScene;

/**
* @class SceneManager
* @brief シーン管理クラス
*/
class SceneManager
{
public:
    /**
    * @brief コンストラクタ
    * @param firstScene 最初に開くシーン
    */
    SceneManager(std::unique_ptr<IScene> firstScene);
    /**
    * @brief デストラクタ
    */
    ~SceneManager();
    /**
    * @brief 更新
    * @param delta 前フレームからの差分時間
    */
    void update(float delta);
    /**
    * @brief 描画
    */
    void draw();
private:
    std::unique_ptr<IScene> mCurrentScene; //!< 現在のシーン
};

} //Scene 