#pragma once
#include <vector>
#include "Main/BoxCollision.h"
#include "Main/ICollisionRegister.h"

namespace Main {


/**
* @class CollisionManager
* @brief �Փ˔���Ǘ�
*/
class CollisionManager : public ICollisionRegister {
public:
    /**
    * @brief �R���X�g���N�^
    */
    CollisionManager();
    /**
    * @brief �f�X�g���N�^
    */
    ~CollisionManager();
    void update();

    virtual void registerCollision(BoxCollision* collision) override;
private:
    std::vector<BoxCollision*> mBoxCollisionList;
};

} //Main 