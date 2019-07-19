#pragma once

#include "Device/Graphics/Light/Light.h"
#include "Utility/Math/Vector3.h"

namespace Graphics {

struct DirectionalLightCBufferStruct;

/**
* @struct DirectionalLightParam
* @brief �f�B���N�V���i�����C�g�p�����[�^
*/
struct DirectionalLightParam {
    Color4 color; //!< �F
    Math::Vector3 dir; //!< �����x�N�g��
};

/**
* @class DirectionalLight
* @brief �f�B���N�V���i�����C�g�N���X
*/
class DirectionalLight final : public Light<DirectionalLightCBufferStruct> {
public:
    /**
    * @brief �R���X�g���N�^
    * @param param �쐬����f�B���N�V���i�����C�g�̃p�����[�^
    */
    DirectionalLight(const DirectionalLightParam& param);
    /**
    * @brief �f�X�g���N�^
    */
    ~DirectionalLight();
    /**
    * @brief �����x�N�g���̐ݒ�
    */
    void setDirection(const Math::Vector3& direction) { mDirection = direction; }
    /**
    * @brief �����x�N�g���̎擾
    */
    const Math::Vector3& getDirection() const { return mDirection; }
private:
    /**
    * @brief �o�b�t�@�Ƀf�[�^��ݒ肷��
    * @param buffer �ݒ肷��o�b�t�@
    */
    void setBuffer(DirectionalLightCBufferStruct* buffer);
private:
    Math::Vector3 mDirection; //!< ���C�g�̕����x�N�g��
};

} //Graphics 