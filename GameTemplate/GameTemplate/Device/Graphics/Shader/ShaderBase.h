#pragma once

#include <memory>
#include <d3d11.h>
#include <wrl/client.h>

namespace Utility {
class ByteReader;
} //Utility 

namespace Graphics {
class GraphicsDeviceManager;
class ResourceSetterToDevice;

/**
* @class ShaderBase
* @brief �V�F�[�_���N���X
*/
class ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    */
    ShaderBase(GraphicsDeviceManager& graphicsDevice);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ShaderBase() = default;
    /**
    * @brief �V�F�[�_���g�p����
    */
    virtual void set() = 0;
protected:
    GraphicsDeviceManager& mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X  
    using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;
    DeviceContext mDeviceContext; //!< �f�o�C�X�R���e�L�X�g
    using ByteReaderPtr = std::unique_ptr<Utility::ByteReader>;
    ByteReaderPtr mByteReader; //!< �o�C�g�f�[�^�ǂݍ���
};

} //Graphics 
