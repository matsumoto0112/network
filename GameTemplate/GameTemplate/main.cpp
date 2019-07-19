#include "Game.h"
#include <memory>
#include <iostream>
#include "Resources/resource.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"
#include "Utility/Math/Vector2.h"
#include "Device/GameDevice.h"
#include "Device/Graphics/Camera/OrthographicCamera.h"
#include "Device/Graphics/Camera/PerspectiveCamera.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/Render/RenderTargetManager.h"
#include "Device/Graphics/Render/DepthStencilView.h"
#include "Device/Graphics/Render/RenderTargetFactory.h"
#include "Scene/SceneManager.h"
#include "Scene/Title.h"
#include "Utility/TimeMeasurement.h"
#include "Utility/Debug.h"
#include "Define/Window.h"
#include "Device/Graphics/Shader/PostEffect.h"
#include "Device/Graphics/Shader/VertexShader.h"
#include "Device/Graphics/Shader/PixelShader.h"

#include "Device/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Device/Graphics/Vertex/Vertex.h"
#include "Device/Graphics/Buffer/Constant/ConstantBuffer.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/Render/IRenderModeChanger.h"
#include "Device/Graphics/Model/Bone.h"
#include "Device/Graphics/Model/Motion.h"
#include "Device/Graphics/Model/Animation.h"
#include "Device/Graphics/Model/AnimationModel.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Utility/FPS.h"
#include "Utility/Console.h"
#include "Device/Window/Window.h"
#include "Device/Window/Procedure/CloseProc.h"
#include "Device/Window/Procedure/DestroyProc.h"
#include "Device/Window/Procedure/EndProc.h"
#include "Device/Graphics/String/TextureString.h"
#include "Device/Window/Procedure/PrintFPSProc.h"
#include "Device/Window/Procedure/ShowCursorProc.h"
#include "Device/Graphics/Camera/FPSCamera.h"
#include "Device/Input/InputManager.h"
#include "Device/Input/Mouse.h"
#include <iomanip>
#include "Utility/AxisDrawer.h"
#include "Define/Path.h"
#include "Device/Window/Procedure/LeftButtonDownProc.h"

using namespace Graphics;
using namespace Math;

#pragma comment(lib , "WSock32.lib")

class MyGame : public Game {
public:
    MyGame() :Game(Math::Vector2((float)Define::Window::WIDTH, (float)Define::Window::HEIGHT)) {};
    ~MyGame() {};
private:
    virtual bool init() override {
        if (!Game::init()) {
            return false;
        }
        auto& window = mGameDevice.getWindow();
        HWND hWnd = window.getHWND();
        window.setProcedureEvent(new Window::DestroyProc());
        window.setProcedureEvent(new Window::CloseProc());
        window.setProcedureEvent(new Window::EndProc());
        window.setProcedureEvent(new Window::PrintFPSProc(hWnd, [&]() {mFPSStr.first = !mFPSStr.first; }));
        window.setProcedureEvent(new Window::LeftButtonDownProc([&]() {mGameDevice.getInputManager().getMouse().setCursorMode(Input::CursorMode::Hide); }));

        Graphics::GraphicsDeviceManager& device = mGameDevice.getDirectX11Device();
        Graphics::RenderTargetFactory factory(device);

        std::unique_ptr<Graphics::OrthographicCamera> twoDCamera3 =
            std::make_unique<Graphics::OrthographicCamera>(device, mScreenSize, factory.createRenderTarget(2, mScreenSize / 4));
        CameraManager& camera = Graphics::CameraManager::getInstance();
        camera.addCamera(Define::CameraType::BackGround, std::move(twoDCamera3));

        std::unique_ptr<Graphics::OrthographicCamera> twoDCamera =
            std::make_unique<Graphics::OrthographicCamera>(device, mScreenSize, factory.createRenderTarget(2, mScreenSize));
        camera.addCamera(Define::CameraType::TwoD, std::move(twoDCamera));

        std::unique_ptr<Graphics::OrthographicCamera> twoDCamera2 =
            std::make_unique<Graphics::OrthographicCamera>(device, mScreenSize, factory.createRenderTarget(2, mScreenSize));
        camera.addCamera(Define::CameraType::UI, std::move(twoDCamera2));

        Graphics::PerspectiveCameraInfo info =
        { Math::Vector3(0, 5.0f, -10.0f), Math::Vector3(0, 0, 0), Math::Vector3(0, 1, 0),
                45.0f, mScreenSize, 0.1f, 10000.0f, };

        std::unique_ptr<Graphics::DepthStencilView> mDepthStencilView = std::make_unique<Graphics::DepthStencilView>(device.getDirectX11Device(),
            (UINT)mScreenSize.x, (UINT)mScreenSize.y, 1, 0);

        std::unique_ptr<Graphics::FPSCamera> threeDCamera =
            std::make_unique<Graphics::FPSCamera>(device,
                info, factory.createRenderTarget(1, mScreenSize, std::move(mDepthStencilView)));

        camera.addCamera(Define::CameraType::ThreeD, std::move(threeDCamera));

        mSceneManager = std::make_unique<Scene::SceneManager>(std::make_unique<Scene::Title>());
        mFPSStr = std::make_pair<bool, std::unique_ptr<Graphics::TextureString>>
            (false,
                std::make_unique<Graphics::TextureString>(device, "0", 28, ""));
        mFPSStr.second->setZOrder(-1.0f);
        mAxisDrawer = std::make_pair<bool, std::unique_ptr<Utility::AxisDrawer>>(
            true,
            std::make_unique<Utility::AxisDrawer>());

        Input::Mouse& mouse = mGameDevice.getInputManager().getMouse();
        mouse.setFixedPosition(Define::Window::getSize() / 2);
        mouse.setCursorMode(Input::CursorMode::Hide);

        return true;
    }
    virtual void update(float deltaTime) override {
        mGameDevice.update();

        Input::Mouse& mouse = mGameDevice.getInputManager().getMouse();
        //右クリックされたらカーソルを表示状態にする
        if (mouse.getMouseDown(Input::MouseButton::Right)) {
            mouse.setCursorMode(Input::CursorMode::Show);
        }
        //if (!mGameDevice.getWindow().isActive()) {
        //    mouse.setCursorMode(Input::CursorMode::Show);
        //}

        mSceneManager->update(deltaTime);
        if (mFPSStr.first) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(0) << mFPSCounter.getFPS();
            mFPSStr.second->setString(ss.str());
        }
    }
    virtual void draw() override {
        Graphics::GraphicsDeviceManager& graphicsDevice = mGameDevice.getDirectX11Device();
        graphicsDevice.drawBegin();
        mSceneManager->draw();

        if (mFPSStr.first) {
            Graphics::CameraManager::getInstance().setRenderingCamera(Define::CameraType::UI);
            mFPSStr.second->draw();
        }
        if (mAxisDrawer.first) {
            Graphics::CameraManager::getInstance().setRenderingCamera(Define::CameraType::ThreeD);
            mAxisDrawer.second->draw();
        }

        graphicsDevice.drawEnd();
    }
    virtual void finalize() override {
        Game::finalize();
    }
private:
    std::unique_ptr<Scene::SceneManager> mSceneManager;
    Utility::FPS mFPSCounter;
    std::pair<bool, std::unique_ptr<Graphics::TextureString>> mFPSStr;
    std::pair<bool, std::unique_ptr<Utility::AxisDrawer>> mAxisDrawer;
};

int main() {
    WSADATA wsaData;

    //WinSock初期化
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        return -1;
    }
    try {
        MyGame().run();
    }
    catch (const std::exception& e) {
        MY_ERROR_WINDOW(false, e.what());
    }
    WSACleanup();
}