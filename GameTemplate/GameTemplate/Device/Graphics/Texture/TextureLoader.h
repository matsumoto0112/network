#pragma once

#include <wincodec.h>
#include <memory>
#include <string>
#include <d3d11.h>

namespace Graphics {
class GraphicsDeviceManager;
class ResourceStructureManager;
class Texture;

/**
* @class TextureLoader
* @brief �e�N�X�`���ǂݍ��݋@
*/
class TextureLoader
{
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    */
    TextureLoader(GraphicsDeviceManager& graphicsDevice);
    /**
    * @brief �f�X�g���N�^
    */
    ~TextureLoader();
    /**
    * @brief �e�N�X�`���ǂݍ���
    * @param filepath �t�@�C���ւ̃p�X
    */
    std::unique_ptr<Texture> load(const std::string& filepath);
private:
    GraphicsDeviceManager& mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    IWICBitmapDecoder* mDecoder; //!< �f�R�[�_�[
    IWICBitmapFrameDecode* mFrame; //!< �t���[���f�R�[�h
    IWICFormatConverter* mConverter; //!< �t�H�[�}�b�g�ϊ���
    IWICImagingFactory* mFactory; //!< �C���[�W������
    D3D11_TEXTURE2D_DESC mTexture2DDesc; //!< �e�N�X�`��2D�f�X�N
    D3D11_SHADER_RESOURCE_VIEW_DESC mSRVDesc; //!< �V�F�[�_�[���\�[�X�r���[�f�X�N
};

} //Graphics 
