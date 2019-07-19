#pragma once

#include <d3d11.h>
#include <wrl/client.h>


namespace Graphics {

class DirectX11GraphicsDevice;
enum class ShaderInputType;

/**
* @enum TextureAddressMode
* @brief �e�N�X�`����UV���W��0�`1�͈̔͊O�̎��̏������@
*/
enum class TextureAddressMode {
    Wrap, //!< ������؂�Ńe�N�X�`���̌J��Ԃ�
    Clamp, //!< 0�`1�ɃN�����v
};

/**
* @enum TextureFilterMode
* @brief �T���v�����O���̃t�B���^�����O���@
*/
enum class TextureFilterMode {
    MinMagMipLinear, //!< �g��k���A�~�b�v���x���ɐ��`��Ԃ��g�p
    MinMagMipPoint,
};

/**
* @brief �T���v���[
* @detail �T���v���[��0�`1�͈̔͊O�̏����A�T���v�����O���̃t�B���^�����O���@��I�����č쐬�ł��܂��B
����ȏ�̂��Ƃ��������ꍇ�̓V�F�[�_�t�@�C�����Œ��ڋL�q���邩�A�쐬�������ID3D11SamplerState���R���X�g���N�^�œn���Ă�������
*/
class Sampler {
private:
    using SamplerState = Microsoft::WRL::ComPtr<ID3D11SamplerState>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param addressMode UV���W�͈͊O���̏������@
    * @param filterMode �T���v�����O���̃t�B���^�����O���@
    */
    Sampler(DirectX11GraphicsDevice& graphicsDevice, TextureAddressMode addressMode, TextureFilterMode filterMode);
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param sampler �T���v���[
    */
    Sampler(DirectX11GraphicsDevice& graphicsDevice, const SamplerState& sampler);
    /**
    * @brief �f�X�g���N�^
    */
    ~Sampler();
    /**
    * @brief �f�[�^�̃Z�b�g
    * @param inputType �ǂ̃V�F�[�_�ɒl�������邩
    * @param slotNum �V�F�[�_�̉��Ԃɂ��̃e�N�X�`���f�[�^�������邩
    */
    void setData(ShaderInputType inputType, UINT slotNumber);
private:
    DirectX11GraphicsDevice& mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    SamplerState mSamplerState; //!< �T���v���[�X�e�[�g
};

} //Graphics 
