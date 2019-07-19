#pragma once
#include <vector>
#include "Main/BoxCollision.h"
#include "Main/ICollisionRegister.h"

namespace Main {


/**
* @class CollisionManager
* @brief 衝突判定管理
*/
class CollisionManager : public ICollisionRegister {
public:
    /**
    * @brief コンストラクタ
    */
    CollisionManager();
    /**
    * @brief デストラクタ
    */
    ~CollisionManager();
    void update();

    virtual void registerCollision(BoxCollision* collision) override;
private:
    std::vector<BoxCollision*> mBoxCollisionList;
};

} //Main 