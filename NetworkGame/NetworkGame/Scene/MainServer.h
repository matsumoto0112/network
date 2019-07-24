#pragma once
#include "Scene/IScene.h"

namespace Network {
class GameServerThread;
} //Network 

namespace Graphics {
class TextureString;
class Sprite2D;
} //Graphics 

namespace Main {
class MainObjectManager;
} //Main 

namespace Scene {

class MainServer : public IScene {
public:
    MainServer(std::unique_ptr<Network::GameServerThread> serverThread);
    ~MainServer();
    virtual void update(float delta) override;
    virtual bool isEndScene() const override;
    virtual void draw() override;
    virtual std::unique_ptr<IScene> end() override;
private:
    std::unique_ptr<Network::GameServerThread> mServerThread;
    std::unique_ptr<Graphics::TextureString> mStr;
    std::unique_ptr<Main::MainObjectManager> mObjectManager;
    std::unique_ptr<Graphics::Sprite2D> mReticule;
    bool mIsSceneEnd;
    bool mWin;
    bool mIsDisconnect;
};

} //Scene 