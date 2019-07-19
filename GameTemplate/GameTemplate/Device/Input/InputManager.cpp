#include "InputManager.h"
#include "Device/Input/Joystick.h"
#include "Device/Input/Keyboard.h"
#include "Device/Input/Mouse.h"
#include "Device/Window/Window.h"
#include "Define/Controller.h"
#include "Device/Input/ID.h"
#include "Utility/Debug.h"

namespace Input {

InputManager::InputManager(Window::Window& mainWindow)
    :mKeyboard(std::make_unique<Keyboard>(mainWindow.getHWND())),
    mMouse(std::make_unique<Mouse>(mainWindow, *mKeyboard)) {
    for (UINT i = 0; i < Define::Controller::CONTROLLER_NUMBER; ++i) {
        mControllers.emplace_back(std::make_unique<Joystick>(static_cast<Input::ID>(i)));
    }
}

InputManager::~InputManager() {}

const Joystick& InputManager::getController(ID playerNumber) const {
    MY_ASSERTION(static_cast<UINT>(playerNumber) < mControllers.size(),
        "プレイヤー番号がインデックスの範囲外です。");
    return *mControllers[static_cast<UINT>(playerNumber)];
}

const Keyboard& InputManager::getKeyboard() const {
    return *mKeyboard;
}

const Mouse& InputManager::getMouse() const {
    return *mMouse;
}

Mouse& InputManager::getMouse() {
    return *mMouse;
}

void InputManager::update() {
    for (auto&& controller : mControllers) {
        controller->update();
    }
    mKeyboard->update();
    mMouse->update();
}

} //Input 
