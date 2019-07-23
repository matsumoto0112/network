#include "MainClient.h"
#include <iostream>
#include "Network/GameClientThread.h"
#include "Device/GameDevice.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/String/TextureString.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Utility/Console.h"
#include "Device/Graphics/Camera/PerspectiveCamera.h"
#include "Device/Graphics/Model/Model.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Main/Player.h"
#include "Main/Stage.h"
#include "Utility/Resource/ResourceManager.h"
#include "Device/Graphics/Texture/TextureLoader.h"
#include "Device/Graphics/Sprite/Sprite2D.h"
#include "Define/Path.h"
#include "Define/Window.h"
#include "Device/Input/InputManager.h"
#include "Device/Input/Mouse.h"
#include "Main/Enemy.h"
#include "Scene/Title.h"
#include "Device/Window/Window.h"
#include "Resources/resource.h"
#include "Main/MainObjectManager.h"

#include "Device/Graphics/Primitive/OBB3D.h"
#include "Device/Graphics/Shader/Effect.h"
#include "Define/Resource/Model.h"
#include "Device/Graphics/Render/IRenderModeChanger.h"
#include "Network/PacketData.h"

namespace Scene {

MainClient::MainClient(std::unique_ptr<Network::GameClientThread> clientThread)
    :mClient(std::move(clientThread)),
    mStr(std::make_unique<Graphics::TextureString>(
        Device::GameDevice::getInstance().getDirectX11Device(), "Client Side", 14, "")),
    mIsSceneEnd(false) {

    Utility::PixelShaderResourceStorage* psResourceManager = Utility::ResourceManager::getInstance().getPixelShader();
    psResourceManager->importResource(Define::PixelShaderType::RedModel, Define::PixelShaderName::RED_MODEL);

    auto sendShootDataToServerFunc = [&](const Math::Vector3& position, const Math::Quaternion& rotate) {
        Network::ShootData data;
        data.shotPosition = position;
        data.rotate = rotate;
        mClient->sendMessage(data);
    };

    auto playerHittedEvent = [&](bool isDead) {
        if (isDead) {
            mIsSceneEnd = true;
        }
        Network::HitData data;
        data.dead = isDead;
        data.bulletID = 0;
        mClient->sendMessage(data);
    };

    mObjectManager = std::make_unique<Main::MainObjectManager>(sendShootDataToServerFunc);
    mObjectManager->registerPlayer(std::make_unique<Main::Player>(*mObjectManager, *mObjectManager, playerHittedEvent));
    mObjectManager->registerEnemy(std::make_unique<Main::Enemy>(*mObjectManager));
    mObjectManager->registerStage(std::make_unique<Main::Stage>(*mObjectManager));

    Graphics::TextureLoader texLoader(Device::GameDevice::getInstance().getDirectX11Device());
    std::shared_ptr<Graphics::Texture> tex = texLoader.load(Define::Path::getInstance().texture() + "reticule.png");
    mReticule = std::make_unique<Graphics::Sprite2D>(Device::GameDevice::getInstance().getDirectX11Device(), tex);
    mReticule->setPosition(Define::Window::getSize() * 0.5f);

    mClient->setDisconnectEvent([&]() {mIsSceneEnd = true; });

}
MainClient::~MainClient() {}


void MainClient::update(float delta) {
    auto recieveTransformData = [&](const std::string& mes) {
        Network::TransformData recieve;
        recieve.decode(mes);
        mObjectManager->recieveTransformData(recieve);
    };
    auto recieveShootData = [&](const std::string& mes) {
        Network::ShootData recieve;
        recieve.decode(mes);
        mObjectManager->shootByOpponent(recieve.shotPosition, recieve.rotate);
    };

    Network::TransformData packet = mObjectManager->createTransformData();
    mClient->sendMessage(packet);

    std::list<std::string> recvMessages = mClient->getAllMessage();

    for (auto&& mes : recvMessages) {
        std::stringstream ss(mes);
        Network::DataType type;
        int tmp;
        ss >> tmp;
        type = (Network::DataType)tmp;
        switch (type) {
        case Network::DataType::Transform:
            recieveTransformData(ss.str());
            break;
        case Network::DataType::Shot:
            recieveShootData(ss.str());
            break;
        default:
            break;
        }
    }

    mObjectManager->update(delta);
}

bool MainClient::isEndScene() const {
    return mIsSceneEnd;
}

void MainClient::draw() {
    Graphics::CameraManager& cameraManager = Graphics::CameraManager::getInstance();
    cameraManager.setRenderingCamera(Define::CameraType::ThreeD);
    mObjectManager->draw();
    cameraManager.setRenderingCamera(Define::CameraType::UI);
    mStr->draw();
    mReticule->draw();
}

std::unique_ptr<IScene> MainClient::end() {
    mClient->end();
    return std::make_unique<Title>();
}
} //Scene 
