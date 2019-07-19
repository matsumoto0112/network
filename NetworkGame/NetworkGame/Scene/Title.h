#pragma once

#include "Scene/IScene.h"

namespace Graphics {
class TextureString;
} //Graphics 

namespace Scene {

class Title : public IScene {
public:
    Title();
    ~Title();
    virtual void update(float delta) override;
    virtual bool isEndScene() const override;
    virtual void draw() override;
    virtual std::unique_ptr<IScene> end() override;
private:
    bool mIsEnd;
    bool mSelectServer;
    std::unique_ptr<Graphics::TextureString> mStr;
};

} //Graphics 