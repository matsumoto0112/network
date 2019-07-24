#pragma once

#include <memory>
#include "Scene/IScene.h"

namespace Graphics {
class TextureString;
} //Graphics 

namespace Scene {

/**
* @class Result
* @brief リザルトシーン
*/
class Result : public IScene {
public:
    /**
    * @brief コンストラクタ
    */
    Result(bool isWin);
    /**
    * @brief デストラクタ
    */
    ~Result();
    virtual void update(float delta) override;

    virtual bool isEndScene() const override;

    virtual void draw() override;

    virtual std::unique_ptr<IScene> end() override;
private:
    bool mIsSceneEnd;
    std::unique_ptr<Graphics::TextureString> mVictoryText;
    std::unique_ptr<Graphics::TextureString> mUI;
};

} //Scene 