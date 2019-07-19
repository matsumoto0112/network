#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include <unordered_map>
#include "Device/Graphics/Render/RasterizerMode.h"
#include "Device/Graphics/Render/IRenderModeChanger.h"
#include "Utility/HashCombine.h"

namespace Graphics {
class DirectX11GraphicsDevice;

/**
* @class RasterizerManager
* @brief ���X�^���C�U�Ǘ�
*/
class RasterizerManager : public IRenderModeChanger
{
public:
    /**
    * @brief �R���X�g���N�^
    * @param device DirectX11�O���t�B�b�N�f�o�C�X    
    */
    RasterizerManager(DirectX11GraphicsDevice& device);
    /**
    * @brief �f�X�g���N�^
    */
    ~RasterizerManager();
    /**
    * @brief ���݂̃J�����O���[�h�̎擾
    */
    CullMode getCullMode() const override;
    /**
    * @brief �h��Ԃ����[�h�̎擾
    */
    FillMode getFillMode() const override;
    /**
    * @brief �`�惂�[�h�̐ݒ�
    * @param cull �J�����O�̎��
    * @param fill �h��Ԃ��̎��
    */
    virtual void setRenderMode(CullMode cull, FillMode fill) override;
private:
    DirectX11GraphicsDevice& mDevice; //!< DirectX11�O���t�B�b�N�f�o�C�X
    std::unordered_map<RasterizerMode, 
        Microsoft::WRL::ComPtr<ID3D11RasterizerState>, 
        RasterizerModeHash, RasterizerModeEqual> mRasStates; //!< �쐬�ς݃��X�^���C�U�X�e�[�g
    RasterizerMode mRasterizerMode; //!< ���݂̃��X�^���C�U�̐ݒ�
};

} //Graphics 