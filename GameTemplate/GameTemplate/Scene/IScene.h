#pragma once

#include <memory>

namespace Scene {

/**
* @class IScene
* @brief シーンインターフェース
*/
class IScene
{
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IScene() = default;
    /**
    * @brief 更新
    * @param delta 前フレームからの差分時間
    */
    virtual void update(float delta) = 0;
    /**
    * @brief シーンが終了しているか
    */
    virtual bool isEndScene() const = 0;
    /**
    * v描画
    */
    virtual void draw() = 0;
    /**
    * @brief シーンの終了処理
    * @return 次のシーン
    */
    virtual std::unique_ptr<IScene> end() = 0;
};

} //Scene 