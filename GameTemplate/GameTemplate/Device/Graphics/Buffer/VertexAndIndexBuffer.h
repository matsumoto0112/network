#pragma once

#include <memory>
#include <vector>
#include <d3d11.h>
#include "Device/Graphics/Vertex/Vertex.h"
#include "Device/Graphics/Buffer/VertexBuffer.h"
#include "Device/Graphics/Buffer/IndexBuffer.h"

namespace Graphics {

class GraphicsDeviceManager;

/**
* @class VertexAndIndexBuffer
* @brief ���_�E�C���f�b�N�X�o�b�t�@���܂Ƃ߂��N���X
*/
class VertexAndIndexBuffer {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @tparam vertices ���_�f�[�^
    * @param indices �C���f�b�N�X�f�[�^
    * @param topology �v���~�e�B�u�g�|���W�[�̎��
    */
    template<class T>
    VertexAndIndexBuffer(GraphicsDeviceManager& graphicsDevice,
        const std::vector<T>& vertices,
        const std::vector<WORD>& indices,
        PrimitiveTopology topology);
    /**
    * @brief �f�X�g���N�^
    */
    ~VertexAndIndexBuffer();

    /**
    * @brief �`�悷��
    * @details �`��O�ɕ`��ɕK�v�ȃf�[�^�𑗂��Ă����K�v������
    */
    void render();
private:
    GraphicsDeviceManager& mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    std::unique_ptr<VertexBuffer> mVertexBuffer; //!< ���_�o�b�t�@
    std::unique_ptr<IndexBuffer> mIndexBuffer; //!< �C���f�b�N�X�o�b�t�@
};

template<class T>
inline VertexAndIndexBuffer::VertexAndIndexBuffer(GraphicsDeviceManager& graphicsDevice,
    const std::vector<T>& vertices,
    const std::vector<WORD>& indices,
    PrimitiveTopology topology)
    :mGraphicsDevice(graphicsDevice),
    mVertexBuffer(std::make_unique<VertexBuffer>(graphicsDevice, vertices)),
    mIndexBuffer(std::make_unique<IndexBuffer>(graphicsDevice, indices, topology)) {}
} //Graphics 