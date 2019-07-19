#include "Game.h"

//���������[�N���o
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h> 
#include <crtdbg.h>  

#include <Windows.h>
#include "Device/GameDevice.h"
#include "Utility/Resource/ResourceManager.h"
#include "Utility/Resource/ResourceInitializer.h"
#include "Device/Input/InputManager.h"
#include "Device/Input/Mouse.h"

Game::Game(const Math::Vector2& screenSize, bool isFullScreen, float fps)
    :mGameDevice(Device::GameDevice::getInstance()),
    mScreenSize(screenSize),
    mIsFullScreen(isFullScreen),
    mFPS(fps) {
    //���������[�N���o
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

Game::~Game() {}

int Game::run() {
    if (!init()) {
        return -1;
    }
    MSG msg;
    //���C�����[�v
    while (isRunning() && !mGameDevice.isEnd()) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            update(1.0f / mFPS);
            draw();
        }
    }
    finalize();
    return 0;
}

bool Game::init() {
    Utility::ResourceManager& resManager = Utility::ResourceManager::getInstance();
    (void)Utility::ResourceInitializeOnStart(resManager);
    return true;
}

void Game::finalize() {
    mGameDevice.finalize();
}

bool Game::isRunning() {
    return !mGameDevice.getInputManager().getKeyboard().getKeyDown(Input::KeyCode::Escape);
}
