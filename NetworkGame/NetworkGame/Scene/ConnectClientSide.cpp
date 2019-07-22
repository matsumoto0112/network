#include "ConnectClientSide.h"
#include <Windows.h>
#include <sstream>
#include "Resources/resource.h"
#include "Device/Window/Dialog/DialogProcedures.h"
#include "Device/Window/Dialog/ClientConnectProc.h"
#include "Device/Window/Dialog/CancelProc.h"
#include "Device/Window/Procedure/CloseProc.h"
#include "Device/Window/Procedure/DestroyProc.h"
#include "Scene/Title.h"
#include "Scene/MainClient.h"
#include "Device/GameDevice.h"
#include "Device/Window/Window.h"
#include "Device/Graphics/String/TextureString.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Network/GameClientThread.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Define/Network.h"
#include "Utility/Resource/ResourceManager.h"
#include "Device/GameDevice.h"
#include "Device/Window/Dialog/DialogWindow.h"
#include "Device/Window/Dialog/DialogProcedures.h"

namespace Scene {

ConnectClientSide::ConnectClientSide()
    : ConnectSceneBase(Device::GameDevice::getInstance().addDialog(
        std::make_unique<Window::DialogWindow>(&Device::GameDevice::getInstance().getWindow(),
            IDD_CLIENT, (DLGPROC)Window::DialogProcedures::ClientDlgProc))),
    mConnectEventProc(nullptr) {
    mConnectEventProc = Window::DialogProcedures::addProcedure(Window::DialogProcType::Client, new Window::ClientConnectProc(
        [&](const std::string& address, int port) {pushConnectButton(address, port); }));

    mConnectCancelEventProc = Window::DialogProcedures::addProcedure(Window::DialogProcType::Client,new Window::CancelProc(
        [&]() {mIsSceneEnd = true; mIsSelectConnect = false;  }));
}

ConnectClientSide::~ConnectClientSide() {
    Window::DialogProcedures::removeProcedure(Window::DialogProcType::Client, mConnectEventProc);
    mConnectEventProc = nullptr;
    Window::DialogProcedures::removeProcedure(Window::DialogProcType::Client, mConnectCancelEventProc);
    mConnectCancelEventProc = nullptr;
}

std::unique_ptr<IScene> ConnectClientSide::end() {
    if (mIsSelectConnect) {
        return std::make_unique<MainClient>(std::move(mClient));
    }
    return std::make_unique<Title>();
}

void ConnectClientSide::pushConnectButton(const std::string& address, int port) {
    //クライアントとしてサーバーと接続
    mClient = std::make_unique<Network::GameClientThread>(Define::Network::MAX_BUFFER_SIZE);
    mClient->setServerAddress(Network::InetSocketAddress(address, port));
    mClient->mDisconnectEvent = [&]() {
        mIsSceneEnd = true;
        mIsSelectConnect = false;
    };

    mClient->mConnectEvent = [&]() {
        mIsSceneEnd = true;
        mIsSelectConnect = true;
    };
    mClient->start();

    Utility::FBXModelResourceStorage* fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Floor, Define::ModelName::FLOOR_NAME);
    fbx->importResource(Define::ModelType::Bullet, Define::ModelName::BULLET_NAME);
    fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    fbx->importResource(Define::ModelType::Enemy, Define::ModelName::ENEMY_NAME);

    mDialogWindow.close();
}

} //Scene 
