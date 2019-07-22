#include "ConnectSceneBase.h"
#include "Device/GameDevice.h"
#include "Device/Window/Dialog/DialogWindow.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/String/TextureString.h"
#include "Device/Window/Dialog/DialogProcedures.h"
#include "Device/Window/Procedure/DestroyProc.h"
#include "Device/Window/Procedure/CloseProc.h"
#include "Device/Window/Dialog/CancelProc.h"

namespace Scene {
ConnectSceneBase::ConnectSceneBase(Window::DialogWindow& dialogWindow)
    :mDialogWindow(dialogWindow),
    mMessage(std::make_unique<Graphics::TextureString>(
        Device::GameDevice::getInstance().getDirectX11Device(),
        "Connecting",
        14,
        "")) {
    //ダイアログの閉じるボタンを無効化
    EnableMenuItem(GetSystemMenu(mDialogWindow.getHandle(), NULL), SC_CLOSE, MF_GRAYED);
}

ConnectSceneBase::~ConnectSceneBase() {}

void ConnectSceneBase::update(float delta) {}

bool ConnectSceneBase::isEndScene() const {
    return mIsSceneEnd;
}

void ConnectSceneBase::draw() {
    Graphics::CameraManager::getInstance().setRenderingCamera(Define::CameraType::UI);
    mMessage->draw();
}

} //Scene 
