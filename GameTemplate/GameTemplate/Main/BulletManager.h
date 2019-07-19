#pragma once

#include <vector>
#include <memory>

namespace Main {
class Bullet;

class BulletManager {
public:
    BulletManager();
    ~BulletManager();
    /**
    * @brief �I�u�W�F�N�g�̒ǉ�
    * @param obj �ǉ�����I�u�W�F�N�g
    * @details ����update���ɒǉ������
    */
    void registerBullet(std::unique_ptr<Bullet> obj);
    void update(float delta);
    void draw();
private:
    using BulletPtr = std::unique_ptr<Bullet>;
    using BulletContainer = std::vector<BulletPtr>;
    BulletContainer mBulletList;
    BulletContainer mAddBulletList;
};

} //Main 