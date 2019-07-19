#pragma once

#include <wrl/client.h>
#include <d3d11.h>

namespace Graphics {

class DirectX11GraphicsDevice;

/**
* @class DepthStencilView
* @brief �[�x�E�X�e���V���r���[
*/
class DepthStencilView {
public:
    /**
    * v�R���X�g���N�^
    * @param device DirectX11�O���t�B�b�N�f�o�C�X
    * @param backBufferWidth �o�b�N�o�b�t�@�̕�
    * @param backBufferHeight �o�b�N�o�b�t�@�̍���
    * @param count �s�N�Z���P�ʂ̃}���`�T���v�����O��
    * @param quality �C���[�W�̕i�����x��
    */
    DepthStencilView(DirectX11GraphicsDevice& device,
        UINT backBufferWidth, UINT backBufferHeight,
        UINT count = 1, UINT quality = 0);
    /**
    * @brief �f�X�g���N�^
    */
    ~DepthStencilView();
    /**
    * @brief �o�b�t�@�̎擾
    */
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> getView() const;
    /**
    * @brief �o�b�t�@�̃N���A
    */
    void clear();
private:
    DirectX11GraphicsDevice& mDevice; //!< DirectX11�O���t�B�b�N�f�o�C�X
    Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencil; //!< �[�x�E�X�e���V���o�b�t�@�p�e�N�X�`��
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView; //!< �[�x�E�X�e���V���o�b�t�@
};
} //Graphics 