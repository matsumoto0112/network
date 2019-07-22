#include "ConnectServerSide.h"
#include <Windows.h>
#include "Scene/Title.h"
#include "Scene/MainServer.h"
#include "Device/Window/Dialog/CancelProc.h"
#include "Device/Window/Dialog/ServerConnectProc.h"
#include "Device/Window/Dialog/DialogProcedures.h"
#include "Device/Window/Procedure/CloseProc.h"
#include "Device/Window/Procedure/DestroyProc.h"
#include "Device/GameDevice.h"
#include "Device/Window/Dialog/InitProc.h"
#include "Resources/resource.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/String/TextureString.h"
#include "Network/GameServerThread.h"
#include "Define/Network.h"
#include "Utility/Resource/ResourceManager.h"
#include "Device/Window/Window.h"
#include "Device/Window/Dialog/CancelProc.h"
#include "Device/Window/Dialog/DialogWindow.h"

namespace Scene {

ConnectServerSide::ConnectServerSide()
    :ConnectSceneBase(Device::GameDevice::getInstance().addDialog(
        std::make_unique<Window::DialogWindow>(&Device::GameDevice::getInstance().getWindow(),
            IDD_SERVER, (DLGPROC)Window::DialogProcedures::ServerDlgProc))) {
    mConnectEventProc = Window::DialogProcedures::addProcedure(Window::DialogProcType::Server, new Window::ServerConnectProc([&](int port) {puchConnectButton(port); }));
    mConnectCancelEventProc = Window::DialogProcedures::addProcedure(Window::DialogProcType::Server, new Window::CancelProc(
        [&]() {mIsSceneEnd = true; mIsSelectConnect = false;  }));
}

ConnectServerSide::~ConnectServerSide() {
    Window::DialogProcedures::removeProcedure(Window::DialogProcType::Server, mConnectEventProc);
    mConnectEventProc = nullptr;
    Window::DialogProcedures::removeProcedure(Window::DialogProcType::Server, mConnectCancelEventProc);
    mConnectCancelEventProc = nullptr;
}

std::unique_ptr<IScene> ConnectServerSide::end() {
    if (mIsSelectConnect) {
        return std::make_unique<MainServer>(std::move(mServerThread));
    }
    return std::make_unique<Title>();
}

void ConnectServerSide::puchConnectButton(int port) {
    mMessage->setString("connect waiting...");
    mServerThread = std::make_unique<Network::GameServerThread>(Define::Network::MAX_BUFFER_SIZE, port);

    mServerThread->mConnectEvent = [&]() {
        mIsSceneEnd = true;
        mIsSelectConnect = true;
        mMessage->setString("connect sucsess");
    };

    mServerThread->start();

    Utility::FBXModelResourceStorage* fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Floor, Define::ModelName::FLOOR_NAME);
    fbx->importResource(Define::ModelType::Bullet, Define::ModelName::BULLET_NAME);
    fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    fbx->importResource(Define::ModelType::Enemy, Define::ModelName::ENEMY_NAME);

    mDialogWindow.close();
}

} //Scene 
