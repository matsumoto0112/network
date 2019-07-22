#pragma once
#include <memory>
#include "Main/GameObject.h"

namespace Main {
class BoxCollision;
class ICollisionRegister;

/**
* @class Wall
* @brief discription
*/
class Wall :public GameObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Wall(Transform transform, ICollisionRegister& collisionRegister);
    /**
    * @brief �f�X�g���N�^
    */
    ~Wall();
private:
    std::unique_ptr<BoxCollision> mBoxCollision;
};

} //Main 