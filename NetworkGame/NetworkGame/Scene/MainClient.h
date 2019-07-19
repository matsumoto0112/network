#pragma once
#include "Scene/IScene.h"

namespace Network {
class GameClientThread;
} //Network 

namespace Graphics {
class TextureString;
class Sprite2D;
} //Graphics 

namespace Main {
class MainObjectManager;
} //Main 

namespace Scene {

class MainClient :public IScene {
public:
    MainClient(std::unique_ptr<Network::GameClientThread> clientThread);
    ~MainClient();
    virtual void update(float delta) override;
    virtual bool isEndScene() const override;
    virtual void draw() override;
    virtual std::unique_ptr<IScene> end() override;
private:
    std::unique_ptr<Network::GameClientThread> mClient;
    std::unique_ptr<Main::MainObjectManager> mObjectManager;
    std::unique_ptr<Graphics::TextureString> mStr;
    std::unique_ptr<Graphics::Sprite2D> mReticule;
    bool mIsSceneEnd;
};

} //Scene 