#pragma once

#include "Device/Graphics/Light/Light.h"
#include "Utility/Math/Vector3.h"
#include "Device/Graphics/Color4.h"
#include "Device/Graphics/Light/Attenuation.h"

namespace Graphics {

struct PointLightCBufferStruct;

/**
* @struct PointLightParam
* @brief �|�C���g���C�g�p�����[�^
*/
struct PointLightParam {
    Color4 color; //!< �F
    Math::Vector3 pos; //!< ���W
    Attenuation attenuation; //!< �����p�����[�^
};

/**
* @class PointLight
* @brief �|�C���g���C�g�N���X
*/
class PointLight final :public Light<PointLightCBufferStruct> {
public:
    /**
    * @brief �R���X�g���N�^
    * @param param �쐬���郉�C�g�̃p�����[�^
    */
    PointLight(const PointLightParam& param);
    /**
    * @brief �f�X�g���N�^
    */
    ~PointLight();
    /**
    * @brief ���W�̐ݒ�
    */
    void setPosition(const Math::Vector3& position) { mPosition = position; }
    /**
    * @brief ���W�̎擾
    */
    const Math::Vector3& getPosition() const { return mPosition; }
    /**
    * @brief �����p�����[�^�̐ݒ�
    */
    void setAttenuation(const Attenuation& attr) { mAttenuation = attr; }
    /**
    * @brief �����p�����[�^�̎擾
    */
    const Attenuation& getAttenuation() const { return mAttenuation; }
private:
    /**
    * @brief �o�b�t�@�Ƀf�[�^��ݒ肷��
    * @param buffer �ݒ肷��o�b�t�@
    */
    void setBuffer(PointLightCBufferStruct* buffer);
private:
    Math::Vector3 mPosition; //!< ���C�g�̍��W
    Attenuation mAttenuation; //!< �����p�����[�^
};

} //Graphics 