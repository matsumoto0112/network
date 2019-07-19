#pragma once

#include <map>
#include <memory>
#include "Utility/Debug.h"
#include "Device/Graphics/Camera/Camera.h"
#include "Define/Render/CameraType.h"
#include "Utility/Singleton.h"

namespace Graphics {

class Quad2D;
class Effect;

/**
* @class CameraManager
* @brief �J�����Ǘ�
*/
class CameraManager : public Utility::Singleton<CameraManager> {
public:
    /**
    * @brief �f�X�g���N�^
    */
    ~CameraManager();
    /**
    * @brief �J�����̒ǉ�
    * @param type �J�����̎��
    * @param camera �ǉ�����J����
    * @details �J���������łɒǉ�����Ă�����G���[�ƂȂ�
    */
    void addCamera(Define::CameraType type, std::unique_ptr<Camera> camera);
    /**
    * @brief �����_�����O����J������؂�ւ���
    * @param type �ύX�������J�����̎��
    */
    void setRenderingCamera(Define::CameraType type);
    /**
    * @brief ���ׂẴJ�����̕`�揈��������
    * @details �J������isActive��false�̏ꍇ�A�`�揈�����s��Ȃ�
    */
    void render();
    /**
    * @brief �J�����̎擾
    * @tparam T �擾����J�����̌^
    * @param type �J�����̎��
    * @return �擾�������^�ɕϊ����ꂽ�J����
    */
    template <class T>
    T& getCamera(Define::CameraType type);
protected:
    /**
    * @brief �R���X�g���N�^
    */
    CameraManager();
private:
    GraphicsDeviceManager& mGraphicsDevice; //!< �O���t�B�b�N�f�o�C�X
    std::map<Define::CameraType, std::unique_ptr<Camera>> mCameras; //!< �J����
    std::unique_ptr<Quad2D> mQuad; //!< ��ʂƓ����T�C�Y�̋�`
    std::unique_ptr<Effect> mBlendEffect; //!< �J�����̃����_�����O���ʂ���������V�F�[�_�[
};

template<class T>
inline T& CameraManager::getCamera(Define::CameraType type) {
    MY_ASSERTION(mCameras.find(type) != mCameras.end(),
        "���o�^�̃J�������Ă΂�܂���");
    Camera& camera = *mCameras[type];
    return dynamic_cast<T&>(camera);
}

} //Graphics 