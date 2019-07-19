#pragma once

#include <vector>
#include <d3d11.h>
#include <memory>
#include <wrl/client.h>
#include "Device/Graphics/Buffer/IndexBufferBindData.h"

namespace Graphics {

//�O���錾
class GraphicsDeviceManager;
class DirectX11GraphicsDevice;

/**
* @class IndexBuffer
* @brief �C���f�b�N�X�o�b�t�@�Ǘ��N���X
*/
class IndexBuffer {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param indices �C���f�b�N�X�f�[�^
    * @param topology �v���~�e�B�u�g�|���W�[�̎��
    */
    IndexBuffer(GraphicsDeviceManager& graphicsDevice,
        const std::vector<WORD>& indices, PrimitiveTopology topology);
    /**
    * @brief �f�X�g���N�^
    */
    ~IndexBuffer();
    /**
    * @brief �C���f�b�N�X�f�[�^�̃Z�b�g
    */
    void setData();
    /**
    * @brief �`��w�߂𑗂�
    */
    void drawCall();
private:
    /**
    * @brief �C���f�b�N�X�f�[�^�̐ݒ�
    * @param indices �C���f�b�N�X�f�[�^
    */
    void setBuffer(const std::vector<WORD>& indices, PrimitiveTopology topology);
private:
    DirectX11GraphicsDevice& mGraphicsDevice; //!< DirectX11�p�O���t�B�b�N�f�o�C�X
    std::unique_ptr<IndexBufferBindData> mData; //!< �C���f�b�N�X�o�b�t�@�̃f�[�^
    UINT mIndexCount; //!< ���_��
};

} //Graphics 