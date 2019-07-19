#include "Mouse.h"
#include "Device/Input/Keyboard.h"
#include "Device/GameDevice.h"
#include "Device/Window/Window.h"
#include "Device/Window/Procedure/ShowCursorProc.h"
#include <iostream>
namespace {
Input::KeyCode cast(Input::MouseButton button) {
    return (Input::KeyCode)button;
}

Math::Vector2 toVector2(const POINT& pos) {
    return Math::Vector2(pos.x, pos.y);
}

POINT toPoint(const Math::Vector2& pos) {
    return { (LONG)pos.x,(LONG)pos.y };
}
}

namespace Input {

Mouse::Mouse(Window::Window& window, Keyboard& keyboard)
    :mMainWindow(window), mKeyboard(keyboard) {}

Mouse::~Mouse() {}

void Mouse::update() {
    mPrevPosition = mPosition;
    POINT pos;
    GetCursorPos(&pos);
    ScreenToClient(mMainWindow.getHWND(), &pos);
    mPosition.x = (float)pos.x;
    mPosition.y = (float)pos.y;
    if (mMode == CursorMode::Hide && mMainWindow.isActive()) {
        pos = toPoint(mFixedPosition);
        ClientToScreen(mMainWindow.getHWND(), &pos);
        SetCursorPos(pos.x, pos.y);
    }
}

const Math::Vector2& Mouse::getMousePosition() const {
    return mPosition;
}

bool Mouse::getMouse(MouseButton button) const {
    //���C���E�B���h�E���A�N�e�B�u��ԂłȂ���Δ������Ȃ�
    if (!mMainWindow.isActive())return false;
    return mKeyboard.getKey(cast(button));
}

bool Mouse::getMouseDown(MouseButton button) const {
    //���C���E�B���h�E���A�N�e�B�u��ԂłȂ���Δ������Ȃ�
    if (!mMainWindow.isActive())return false;
    return mKeyboard.getKeyDown(cast(button));
}

bool Mouse::getMouseUp(MouseButton button) const {
    //���C���E�B���h�E���A�N�e�B�u��ԂłȂ���Δ������Ȃ�
    if (!mMainWindow.isActive())return false;
    return mKeyboard.getKeyUp(cast(button));
}

Math::Vector2 Mouse::getMove() const {
    //���C���E�B���h�E���A�N�e�B�u��ԂłȂ���Δ������Ȃ�
    if (!mMainWindow.isActive())return Math::Vector2::ZERO;

    if (mMode == CursorMode::Show) {
        return mPosition - mPrevPosition;
    }
    return mPosition - mFixedPosition;
}

void Mouse::setFixedPosition(const Math::Vector2& position) {
    mFixedPosition = position;
}

void Mouse::setCursorMode(CursorMode mode) {
    //�ύX�̕K�v���Ȃ�
    if (mode == mMode)return;
    mMode = mode;
    if (mode == CursorMode::Show) {
        ShowCursor(TRUE);
    }
    else {
        ShowCursor(FALSE);
    }
}

} //Input 
