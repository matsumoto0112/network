#pragma once
#include "Device/Graphics/Color4.h"
#include <functional>

namespace Graphics {
class GraphicsDeviceManager;
struct PointLightCBufferStruct;

/**
* @class Light
* @brief ���C�g���N���X
* @tparam T �o�b�t�@�ɓ]������\����
*/
template <class T>
class Light {
    using SetBufferFunc = std::function<void(T*)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param color ���C�g�̐F
    * @param func �o�b�t�@�ɓ]������ۂɎg�p����֐�
    */
    Light(const Color4& color, SetBufferFunc func);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Light() = default;
    /**
    * @brief �A�N�e�B�u�t���O��ύX����
    */
    void setActive(bool activeFlag) { mIsActive = activeFlag; }
    /**
    * @brief �A�N�e�B�u��Ԃ�
    */
    bool isActive() const { return mIsActive; }
    /**
    * @brief �F�̐ݒ�
    */
    void setColor(const Color4& color) { mColor = color; }
    /**
    * @brief �F�̎擾
    */
    const Color4& getColor() const { return mColor; }
    /**
    * @brief �o�b�t�@�Ƀ��C�g�̃f�[�^��]������
    */
    void setParamToBuffer(T* buffer);
protected:
    Color4 mColor; //!< �F
    bool mIsActive; //!< �A�N�e�B�u��Ԃ�
    SetBufferFunc mFunc; //!< �o�b�t�@�Ƀf�[�^��]������ۂ̊֐�
};

template<class T>
Light<T>::Light(const Color4& color, SetBufferFunc func)
    :mColor(color), mIsActive(true), mFunc(func) {}

template<class T>
inline void Light<T>::setParamToBuffer(T* buffer) {
    mFunc(buffer);
}

} //Graphics 