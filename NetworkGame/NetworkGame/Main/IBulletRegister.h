#pragma once
#include <memory>

namespace Main {
class Bullet;
/**
* @class IBulletRegister
* @brief 弾の追加インターフェース
*/
class IBulletRegister {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IBulletRegister() = default;

    virtual void registerBullet(std::unique_ptr<Bullet> bullet) = 0;
};

} //Main 