#include "GameDevice.h"
#include "Utility/Debug.h"
#include "Window/Window.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Define/Window.h"
#include "Device/Input/InputManager.h"

namespace Device {

Window::Window& GameDevice::getWindow() const {
    return *mMainWindow;
}

Graphics::GraphicsDeviceManager& GameDevice::getDirectX11Device() const {
    return *mGraphicsDevice;
}

Input::InputManager& GameDevice::getInputManager() const {
    return *mInputManager;
}

void GameDevice::update() {
    mInputManager->update();
}

bool GameDevice::isEnd() const {
    return mMainWindow->isClosed();
}

void GameDevice::finalize() {
    mGraphicsDevice->cleanupDevice();
    mMainWindow->quit();
}

GameDevice::GameDevice() {
    const Math::Vector2 screenSize(
        static_cast<float>(Define::Window::WIDTH),
        static_cast<float>(Define::Window::HEIGHT));
    mMainWindow = std::make_unique<Window::Window>(
        screenSize,
        Math::Vector2(100, 100),
        Define::Window::TITLE,
        true);

    mGraphicsDevice = std::make_unique<Graphics::GraphicsDeviceManager>();
    mGraphicsDevice->init(
        mMainWindow->getHWND(),
        screenSize,
        false);

    mInputManager = std::make_unique<Input::InputManager>(*mMainWindow);

}

GameDevice::~GameDevice() {}


} //Device 
