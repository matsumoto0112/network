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
#include "Resources/resource.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/String/TextureString.h"
#include "Network/GameServerThread.h"
#include "Define/Network.h"
#include "Utility/Resource/ResourceManager.h"

namespace Scene {

ConnectServerSide::ConnectServerSide()
    :mIsSceneEnd(false), mIsSelectConnect(false),
    mStr(std::make_unique<Graphics::TextureString>(
        Device::GameDevice::getInstance().getDirectX11Device(),
        "Connecting",
        14,
        "")) {
    Window::DialogProcedures::mServerDlgProc.emplace_back(std::make_unique<Window::ServerConnectProc>(
        [&](int port) {puchConnectButton(port); }));
    Window::DialogProcedures::mServerDlgProc.emplace_back(std::make_unique<Window::CancelProc>(
        [&]() {mIsSceneEnd = true; mIsSelectConnect = false; }));
    Window::DialogProcedures::mServerDlgProc.emplace_back(std::make_unique<Window::DestroyProc>());
    Window::DialogProcedures::mServerDlgProc.emplace_back(std::make_unique<Window::CloseProc>());
    mDlg = CreateDialog((HINSTANCE)GetModuleHandle(NULL),
        (LPSTR)IDD_SERVER, NULL, (DLGPROC)Window::DialogProcedures::ServerDlgProc);
    EnableMenuItem(GetSystemMenu(mDlg, NULL), SC_CLOSE, MF_GRAYED);
    ShowWindow(mDlg, SW_SHOW);
}

ConnectServerSide::~ConnectServerSide() {
    Window::DialogProcedures::mServerDlgProc.clear();
}

void ConnectServerSide::update(float delta) {}

bool ConnectServerSide::isEndScene() const {
    return mIsSceneEnd;
}

void ConnectServerSide::draw() {
    Graphics::CameraManager::getInstance().setRenderingCamera(Define::CameraType::UI);
    mStr->draw();
}

std::unique_ptr<IScene> ConnectServerSide::end() {
    if (mIsSelectConnect) {
        return std::make_unique<MainServer>(std::move(mServerThread));
    }
    return std::make_unique<Title>();
}

void ConnectServerSide::puchConnectButton(int port) {
    mServerThread = std::make_unique<Network::GameServerThread>(Define::Network::MAX_BUFFER_SIZE, port);

    mServerThread->mConnectEvent = [&]() {
        mIsSceneEnd = true;
        mIsSelectConnect = true;
    };
    mServerThread->start();

    Utility::FBXModelResourceStorage* fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Floor, Define::ModelName::FLOOR_NAME);
    fbx->importResource(Define::ModelType::Bullet, Define::ModelName::BULLET_NAME);
    fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    fbx->importResource(Define::ModelType::Enemy, Define::ModelName::ENEMY_NAME);

    SendMessage(mDlg, WM_CLOSE, 0, 0);
}

} //Scene 
