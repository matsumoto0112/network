#include "Title.h"
#include <iostream>
#include "Device/GameDevice.h"
#include "Device/Graphics/String/TextureString.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Input/InputManager.h"
#include "Device/Input/Keyboard.h"
#include "Device/Graphics/Model/Model.h"
#include "Device/Graphics/Model/OBJLoader.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Device/Graphics/Texture/TextureLoader.h"
#include "Device/Graphics/Sprite/Sprite2D.h"
#include "Define/Path.h"
#include "Device/Graphics/Camera/PerspectiveCamera.h"
#include "Device/Graphics/Camera/OrthographicCamera.h"
#include "Define/Window.h"
#include "Scene/ConnectServerSide.h"
#include "Device/Graphics/Light/PointLight.h"
#include "Device/Graphics/Light/Attenuation.h"
#include "Device/Graphics/Light/LightManager.h"
#include "Utility/Random.h"
#include "Utility/FPS.h"
#include "Utility/Console.h"
#include "Scene/MainClient.h"
#include "Scene/ConnectClientSide.h"
#include "Scene/MainServer.h"

namespace Scene {

Title::Title()
    : mIsEnd(false), mSelectServer(false),
    mStr(std::make_unique<Graphics::TextureString>(
        Device::GameDevice::getInstance().getDirectX11Device(), "TITLE", 14, "")) {}

Title::~Title() {}

static int cnt = 0;

void Title::update(float delta) {
    const Input::Keyboard& key = Device::GameDevice::getInstance().getInputManager().getKeyboard();
    if (key.getKeyDown(Input::KeyCode::S)) {
        mIsEnd = true;
        mSelectServer = true;
    }
    else if (key.getKeyDown(Input::KeyCode::C)) {
        mIsEnd = true;
        mSelectServer = false;
    }
}

bool Title::isEndScene() const {
    return mIsEnd;
}

void Title::draw() {
    Graphics::CameraManager::getInstance().setRenderingCamera(Define::CameraType::UI);
    mStr->draw();
}

std::unique_ptr<IScene> Title::end() {
    if (mSelectServer) {
        return std::make_unique<ConnectServerSide>();
    }
    else {
        return std::make_unique<ConnectClientSide>();
    }
}

} //Scene 
