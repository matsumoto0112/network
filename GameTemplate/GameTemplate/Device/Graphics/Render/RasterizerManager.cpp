#include "RasterizerManager.h"
#include "Device/Graphics/DirectX11GraphicsDevice.h"
#include "Utility/Debug.h"

namespace {

Microsoft::WRL::ComPtr<ID3D11RasterizerState>
createRasState(Microsoft::WRL::ComPtr<ID3D11Device> device, Graphics::CullMode cullMode, Graphics::FillMode fillMode) {
    D3D11_CULL_MODE cm;
    switch (cullMode) {
    case Graphics::CullMode::Front:
        cm = D3D11_CULL_FRONT;
        break;
    case Graphics::CullMode::Back:
        cm = D3D11_CULL_BACK;
        break;
    case Graphics::CullMode::None:
        cm = D3D11_CULL_NONE;
        break;
    default:
        MY_ASSERTION(false, "�J�����O���[�h���s���ł��B");
        break;
    }

    D3D11_FILL_MODE fm;
    switch (fillMode) {
    case Graphics::FillMode::Solid:
        fm = D3D11_FILL_SOLID;
        break;
    case Graphics::FillMode::WireFrame:
        fm = D3D11_FILL_WIREFRAME;
        break;
    default:
        MY_ASSERTION(false, "�t�B�����[�h���s���ł��B");
        break;
    }

    // ���X�^���C�U�̐ݒ�
    D3D11_RASTERIZER_DESC rdc = {};
    rdc.CullMode = cm; //!< �o�b�N�J�����O
    rdc.FillMode = fm; //!< �ʂ�h��Ԃ�

    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasState;
    HRESULT hr = device->CreateRasterizerState(&rdc, &rasState);
    MY_ASSERTION(SUCCEEDED(hr), "���X�^���C�U�X�e�[�g�쐬���s");
    return rasState;
}

}
namespace Graphics {

RasterizerManager::RasterizerManager(DirectX11GraphicsDevice& device)
    :mDevice(device) {
    //���X�^���C�U�X�e�[�g�쐬
    mRasterizerMode.mCullMode = CullMode::Back; //!< �w�ʃJ�����O
    mRasterizerMode.mFillMode = FillMode::Solid; //!< �ʂ�h��Ԃ�
    mRasStates.emplace(mRasterizerMode,
        createRasState(mDevice.getDevice().Get(), mRasterizerMode.mCullMode, mRasterizerMode.mFillMode));
}

RasterizerManager::~RasterizerManager() {}

CullMode RasterizerManager::getCullMode() const {
    return mRasterizerMode.mCullMode;
}

FillMode RasterizerManager::getFillMode() const {
    return mRasterizerMode.mFillMode;
}

void RasterizerManager::setRenderMode(CullMode cull, FillMode fill) {
    mRasterizerMode.mCullMode = cull;
    mRasterizerMode.mFillMode = fill;
    //�Z�b�g���郉�X�^���C�U�X�e�[�g�����݂��Ȃ���ΐV�����쐬
    auto find = mRasStates.find(mRasterizerMode);
    if (find == mRasStates.end()) {
        Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasState =
            createRasState(mDevice.getDevice().Get(), mRasterizerMode.mCullMode, mRasterizerMode.mFillMode);

        mRasStates.emplace(RasterizerMode{ mRasterizerMode.mCullMode,mRasterizerMode.mFillMode }, rasState);
        mDevice.getContext()->RSSetState(rasState.Get());
    }
    else {
        mDevice.getContext()->RSSetState(find->second.Get());
    }
}

} //Graphics 
