#pragma once

#include <memory>
#include "Scene/IScene.h"

namespace Graphics {
class TextureString;
} //Graphics 

namespace Scene {

/**
* @class Result
* @brief ���U���g�V�[��
*/
class Result : public IScene {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Result(bool isWin);
    /**
    * @brief �f�X�g���N�^
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