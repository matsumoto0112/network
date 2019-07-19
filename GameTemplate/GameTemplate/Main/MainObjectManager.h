#pragma once
#include <memory>
#include <vector>
#include "Main/IBulletRegister.h"
#include "Main/ICollisionRegister.h"

namespace Network {
class TransformData;
} //Network 

namespace Main {
class Player;
class Enemy;
class Stage;
class BulletManager;
class GameObject;
class CollisionManager;

class MainObjectManager :public IBulletRegister, public ICollisionRegister {
public:
    MainObjectManager();
    ~MainObjectManager();

    void registerPlayer(std::unique_ptr<Player> player);
    void registerEnemy(std::unique_ptr<Enemy> enemy);
    void registerStage(std::unique_ptr<Stage> stage);

    void update(float delta);
    void draw();
    Network::TransformData createTransformData() const;
    void recieveTransformData(const Network::TransformData& data);
    virtual void registerBullet(std::unique_ptr<Bullet> bullet) override;
    virtual void registerCollision(BoxCollision* collision) override;
private:
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<Enemy> mEnemy;
    std::unique_ptr<Stage> mStage;
    std::unique_ptr<BulletManager> mBulletManager;
    std::unique_ptr<CollisionManager> mCollisionManager;
};

} //Main 