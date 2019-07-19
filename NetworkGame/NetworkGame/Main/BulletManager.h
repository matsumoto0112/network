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
    * @brief オブジェクトの追加
    * @param obj 追加するオブジェクト
    * @details 次回update時に追加される
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