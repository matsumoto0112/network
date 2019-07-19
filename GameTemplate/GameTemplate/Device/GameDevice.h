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
* @brief �Q�[���@��Ǘ�
*/
class GameDevice : public Utility::Singleton<GameDevice> {
private:
    using WindowPtr = std::unique_ptr<Window::Window>;
    using GraphicsDevicePtr = std::unique_ptr<Graphics::GraphicsDeviceManager>;
    using InputManagerPtr = std::unique_ptr<Input::InputManager>;
public:
    /**
    * @brief ���C���E�B���h�E�̎擾
    */
    Window::Window& getWindow() const;
    /**
    * @brief �O���t�B�b�N�f�o�C�X�̎擾
    */
    Graphics::GraphicsDeviceManager& getDirectX11Device() const;

    /**
    * @brief ���͊Ǘ��f�o�C�X�̎擾
    */
    Input::InputManager& getInputManager() const;

    /**
    * @brief �f�o�C�X�̍X�V
    */
    void update();

    /**
    * @brief �Q�[�����I�����Ă��邩
    */
    bool isEnd() const;
    /**
    * @brief �I������
    */
    void finalize();
protected:
    /**
    * @brief �R���X�g���N�^
    * @details private�ɂ����unique_ptr���쐬�ł��Ȃ�����protected
    */
    GameDevice();
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~GameDevice();
private:
    WindowPtr mMainWindow; //!< ���C���E�B���h�E
    GraphicsDevicePtr mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    InputManagerPtr mInputManager; //!< ���͊Ǘ�
};

} //Device 
