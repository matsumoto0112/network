#pragma once

#include <memory>
#include <vector>
#include "Utility/Math/Vector3.h"
#include "Device/Graphics/Color4.h"
#include "Device/Graphics/Light/Attenuation.h"
#include "Utility/Debug.h"
#include "Device/Graphics/Light/PointLight.h"
#include "Device/Graphics/Light/DirectionalLight.h"

namespace Graphics {

class GraphicsDeviceManager;

/**
* @class LightManager
* @brief ���C�g�Ǘ���
*/
class LightManager {
public:
    /**
    * @brief �R���X�g���N�^
    * @param device �O���t�B�b�N�f�o�C�X
    */
    LightManager(GraphicsDeviceManager& device);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~LightManager();
    /**
    * @brief ���C�g�̒ǉ�
    * @param param ���C�g�̃p�����[�^
    * @return �ǉ����ꂽ���C�g�̃C���f�b�N�X
    */
    int addLight(const PointLightParam& param);
    /**
    * @brief ���C�g�̒ǉ�
    * @param param ���C�g�̃p�����[�^
    * @return �ǉ����ꂽ���C�g�̃C���f�b�N�X
    */
    int addLight(const DirectionalLightParam& param);
    /**
    * @brief ���C�g�̎擾
    * @tparam T �擾���������C�g�̌^
    * @param index ���C�g�̃C���f�b�N�X
    */
    template <class T>
    T& getLight(int index);
    /**
    * @brief �o�b�t�@�Ƀf�[�^��]������
    */
    void set();
private:
    GraphicsDeviceManager& mDevice; //!< �O���t�B�b�N�f�o�C�X
    std::vector<std::unique_ptr<DirectionalLight>> mDirectionalLights; //!< �f�B���N�V���i�����C�g���X�g
    std::vector<std::unique_ptr<PointLight>> mPointLights; //!< �|�C���g���C�g���X�g
};

template<>
inline PointLight& LightManager::getLight(int id) {
    MY_ASSERTION(id < (int)mPointLights.size(),
        "�C���f�b�N�X���z��͈̔͊O�ł��B");
    return *mPointLights[id];
}

template <>
inline DirectionalLight& LightManager::getLight(int id) {
    MY_ASSERTION(id < (int)mDirectionalLights.size(),
        "�C���f�b�N�X���z��͈̔͊O�ł��B");
    return *mDirectionalLights[id];
}

template <class T>
inline T& LightManager::getLight(int id) {
    static_assert(false, "exist undefined light type");
}

} //Graphics 