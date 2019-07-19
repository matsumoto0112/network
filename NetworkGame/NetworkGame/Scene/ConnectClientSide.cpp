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

namespace Scene {

ConnectClientSide::ConnectClientSide()
    :mIsSceneEnd(false), mIsSelectConnect(false),
    mStr(std::make_unique<Graphics::TextureString>(
        Device::GameDevice::getInstance().getDirectX11Device(),
        "Connecting",
        14,
        "")) {

    //ダイアログ作成
    Window::DialogProcedures::mClientDlgProc.emplace_back(std::make_unique<Window::ClientConnectProc>(
        [&](const std::string& address, int port) {pushConnectButton(address, port); }));
    Window::DialogProcedures::mClientDlgProc.emplace_back(std::make_unique<Window::CancelProc>(
        [&]() {mIsSceneEnd = true; mIsSelectConnect = false; }));
    Window::DialogProcedures::mClientDlgProc.emplace_back(std::make_unique<Window::DestroyProc>());
    Window::DialogProcedures::mClientDlgProc.emplace_back(std::make_unique<Window::CloseProc>());
    mDlg = CreateDialog((HINSTANCE)GetModuleHandle(NULL),
        (LPSTR)IDD_CLIENT, NULL, (DLGPROC)Window::DialogProcedures::ClientDlgProc);
    EnableMenuItem(GetSystemMenu(mDlg, NULL), SC_CLOSE, MF_GRAYED);
    ShowWindow(mDlg, SW_SHOW);
}

ConnectClientSide::~ConnectClientSide() {
    Window::DialogProcedures::mClientDlgProc.clear();
}

void ConnectClientSide::update(float delta) {}

bool ConnectClientSide::isEndScene() const {
    return mIsSceneEnd;
}

void ConnectClientSide::draw() {
    Graphics::CameraManager::getInstance().setRenderingCamera(Define::CameraType::UI);
    mStr->draw();
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

    SendMessage(mDlg, WM_CLOSE, 0, 0);
}

} //Scene 
