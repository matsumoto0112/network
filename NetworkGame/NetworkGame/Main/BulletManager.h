#pragma once

#include <vector>
#include <memory>
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Quaternion.h"

namespace Main {
class Bullet;
class BulletFactory;
class ICollisionRegister;

class BulletManager {
public:
    BulletManager(ICollisionRegister& collisionRegister);
    ~BulletManager();
    /**
    * @brief �I�u�W�F�N�g�̒ǉ�
    * @details ����update���ɒǉ������
    */
    void shoot(const Math::Vector3& position, const Math::Quaternion& rotate);
    void shootByOpponent(const Math::Vector3& position, const Math::Quaternion& rotate);
    void update(float delta);
    void draw();
private:
    using BulletPtr = std::unique_ptr<Bullet>;
    using BulletContainer = std::vector<BulletPtr>;
    BulletContainer mBulletList;
    BulletContainer mAddBulletList;
    std::unique_ptr<BulletFactory> mBulletFactory;
};

} //Main 