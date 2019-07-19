#pragma once

#pragma comment(linker, "/entry:mainCRTStartup")
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")

#include <vector>
#include <memory>
#include "Utility/Singleton.h"

namespace Window {
class Window;
} //Window 
namespace Graphics {
class GraphicsDeviceManager;
} //Graphics 
namespace Input {
class InputManager;
} //Input 

namespace Device {

/**
* @class GameDevice
* @brief ゲーム機器管理
*/
class GameDevice : public Utility::Singleton<GameDevice> {
private:
    using WindowPtr = std::unique_ptr<Window::Window>;
    using GraphicsDevicePtr = std::unique_ptr<Graphics::GraphicsDeviceManager>;
    using InputManagerPtr = std::unique_ptr<Input::InputManager>;
public:
    /**
    * @brief メインウィンドウの取得
    */
    Window::Window& getWindow() const;
    /**
    * @brief グラフィックデバイスの取得
    */
    Graphics::GraphicsDeviceManager& getDirectX11Device() const;

    /**
    * @brief 入力管理デバイスの取得
    */
    Input::InputManager& getInputManager() const;

    /**
    * @brief デバイスの更新
    */
    void update();

    /**
    * @brief ゲームが終了しているか
    */
    bool isEnd() const;
    /**
    * @brief 終了処理
    */
    void finalize();
protected:
    /**
    * @brief コンストラクタ
    * @details privateにするとunique_ptrを作成できないためprotected
    */
    GameDevice();
    /**
    * @brief デストラクタ
    */
    virtual ~GameDevice();
private:
    WindowPtr mMainWindow; //!< メインウィンドウ
    GraphicsDevicePtr mGraphicsDevice; //!< グラフィックデバイス
    InputManagerPtr mInputManager; //!< 入力管理
};

} //Device 
