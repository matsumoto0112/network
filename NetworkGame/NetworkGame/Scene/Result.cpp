#include "Result.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/GameDevice.h"
#include "Device/Graphics/String/TextureString.h"
#include "Device/Input/Keyboard.h"
#include "Device/Input/InputManager.h"
#include "Scene/Title.h"
#include "Device/Graphics/Camera/CameraManager.h"

namespace Scene {
Result::Result(bool isWin)
    :mIsSceneEnd(false),
    mVictoryText(nullptr),
    mUI(nullptr) {
    Graphics::GraphicsDeviceManager& device = Device::GameDevice::getInstance().getDirectX11Device();
    std::string text = isWin ? "WIN" : "LOSE";
    mVictoryText = std::make_unique<Graphics::TextureString>(device, text, 42, "");
    mVictoryText->setPosition(Math::Vector2(100, 100));
    mUI = std::make_unique<Graphics::TextureString>(device, "push space to title", 42, "");
    mUI->setPosition(Math::Vector2(Math::Vector2(100, 400)));
}

Result::~Result() {}

void Result::update(float delta) {
    auto& key = Device::GameDevice::getInstance().getInputManager().getKeyboard();
    if (key.getKeyDown(Input::KeyCode::Space)) {
        mIsSceneEnd = true;
    }
}

bool Result::isEndScene() const {
    return mIsSceneEnd;
}

void Result::draw() {
    Graphics::CameraManager::getInstance().setRenderingCamera(Define::CameraType::UI);
    mVictoryText->draw();
    mUI->draw();
}

std::unique_ptr<IScene> Result::end() {
    return std::make_unique<Scene::Title>();
}
} //Scene 
