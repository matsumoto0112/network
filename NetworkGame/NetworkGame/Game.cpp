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

#include "Scene/ConnectServerSide.h"
#include "Device/Window/Window.h"

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
    MSG msg = {};
    //���C�����[�v
    while (true) {
        if (!isRunning()) {
            break;
        }
        if (mGameDevice.isEnd()) {
            break;
        }
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            bool isProcced = !(Scene::ConnectServerSide::DLGHANDLE && IsDialogMessage(Scene::ConnectServerSide::DLGHANDLE, &msg));
            if (isProcced) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
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
