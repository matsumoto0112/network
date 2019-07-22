#pragma once
#include <memory>
#include <vector>
#include <functional>
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

class MainObjectManager :public IShooter, public ICollisionRegister {
    using ShootSendOpponentFunc = std::function<void(const Math::Vector3&, const Math::Quaternion&)>;
public:
    MainObjectManager(ShootSendOpponentFunc func);
    ~MainObjectManager();

    void registerPlayer(std::unique_ptr<Player> player);
    void registerEnemy(std::unique_ptr<Enemy> enemy);
    void registerStage(std::unique_ptr<Stage> stage);

    void update(float delta);
    void draw();
    Network::TransformData createTransformData() const;
    void recieveTransformData(const Network::TransformData& data);
    virtual void shoot(const Math::Vector3& position, const Math::Quaternion& rotate) override;
    virtual void shootByOpponent(const Math::Vector3& position, const Math::Quaternion& rotate);
    virtual void registerCollision(BoxCollision* collision) override;
    virtual void removeCollision(BoxCollision* collision) override;
private:
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<Enemy> mEnemy;
    std::unique_ptr<Stage> mStage;
    std::unique_ptr<BulletManager> mBulletManager;
    std::unique_ptr<CollisionManager> mCollisionManager;
    ShootSendOpponentFunc mSendFunc;
};

} //Main 