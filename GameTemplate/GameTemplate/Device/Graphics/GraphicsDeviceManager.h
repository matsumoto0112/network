#pragma once

#include <array>
#include <memory>
#include <wrl/client.h>
#include <unordered_map>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dCompiler.lib")
#include <d3d11.h>
#include "Utility/Math/Vector2.h"
#include "Device/Graphics/Color4.h"

namespace Graphics {

class SpriteRenderer;
class ConstantBufferManager;
class ConstantBufferManager;
class PrimitiveDataStorage;
class DirectX11GraphicsDevice;
class RenderTargetManager;
class AlphaBlend;
class IRenderModeChanger;
class RasterizerManager;
class LightManager;
class Sampler;

/**
* @class GraphicsDeviceManager
*/
class GraphicsDeviceManager {
    using Vec2 = Math::Vector2;
public:
    /**
    * @brief �R���X�g���N�^
    */
    GraphicsDeviceManager();
    /**
    * @brief �f�X�g���N�^
    */
    ~GraphicsDeviceManager();
    /**
    * @brief ������
    * @param hWnd �E�B���h�E�n���h��
    * @param screenSize �E�B���h�E�̑傫��
    * @param isFullScreen �t���X�N���[�����H
    */
    bool init(HWND hWnd, const Vec2& screenSize, bool isFullScreen);
    /**
    * @brief �f�o�C�X�̏I������
    */
    void cleanupDevice();
    /**
    * @brief �`��J�n
    */
    void drawBegin();
    /**
    * @brief �`��I��
    */
    void drawEnd();
    /**
    * @brief �f�o�C�X�̎擾
    */
    Microsoft::WRL::ComPtr<ID3D11Device> getDevice() const;
    /**
    * @brief �f�o�C�X�R���e�L�X�g�̎擾
    */
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getContext() const;
    /**
    * @brief �X�v���C�g�`���̎擾
    */
    SpriteRenderer& getSpriteRenderer() const { return *mSpriteRenderer; }
    /**
    * @brief �R���X�^���g�o�b�t�@�Ǘ��҂̎擾
    */
    ConstantBufferManager& getConstantBufferManager() const { return *mConstantBufferManager; }
    /**
    * @brief �v���~�e�B�u�Ǘ��҂̎擾
    */
    PrimitiveDataStorage& getPrimtiveStorage() const { return *mPrimitiveDataStorage; }
    /**
    * @brief �����_�[�^�[�Q�b�g�̊Ǘ��҂̎擾
    */
    RenderTargetManager& getRenderTargetManager() const { return *mRenderTargetManager; }

    LightManager& getLightManager() const { return *mLightManager; }

    /**
    * @brief �X�N���[���T�C�Y�̎擾
    */
    const Vec2& getScreenSize() const { return mScreenSize; }
    /**
    * @brief �`�惂�[�h�ύX��̎擾
    */
    IRenderModeChanger& getRenderModeChanger() const;
    /**
    * @brief DirectX11�p�O���t�B�b�N�f�o�C�X�̎擾
    */
    DirectX11GraphicsDevice& getDirectX11Device() const { return *mGraphicsDevice.get(); }
private:
    std::unique_ptr<DirectX11GraphicsDevice> mGraphicsDevice; //!< DirectX11�p�O���t�B�b�N�f�o�C�X
    std::unique_ptr<RenderTargetManager> mRenderTargetManager; //!< �����_�[�^�[�Q�b�g�̊Ǘ���
    std::unique_ptr<AlphaBlend> mAlphaBlend; //!< �A���t�@�u�����h
    std::unique_ptr<RasterizerManager> mRasterizerManager; //!< ���X�^���C�U�Ǘ�
    std::unique_ptr<SpriteRenderer> mSpriteRenderer; //!< �X�v���C�g�`���
    std::unique_ptr<ConstantBufferManager> mConstantBufferManager; //!< �R���X�^���g�o�b�t�@�Ǘ���
    std::unique_ptr<PrimitiveDataStorage> mPrimitiveDataStorage; //!< �v���~�e�B�u�`��I�u�W�F�N�g�ۑ�
    std::unique_ptr<LightManager> mLightManager;
    std::unique_ptr<Sampler> mDefaultSampler; //!< �f�t�H���g�̃T���v���[
    Vec2 mScreenSize; //!< �X�N���[���̑傫��
};
} //Graphics 