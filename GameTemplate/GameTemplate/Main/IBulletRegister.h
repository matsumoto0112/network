#pragma once
#include <memory>

namespace Main {
class Bullet;
/**
* @class IBulletRegister
* @brief �e�̒ǉ��C���^�[�t�F�[�X
*/
class IBulletRegister {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IBulletRegister() = default;

    virtual void registerBullet(std::unique_ptr<Bullet> bullet) = 0;
};

} //Main 