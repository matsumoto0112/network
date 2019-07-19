#pragma once
#include "Utility/Transform.h"
#include "Utility/Math/OBB3D.h"
#include <vector>

namespace Main {
class GameObject;
/**
* @class BoxCollision
* @brief �{�b�N�X�̂����蔻��
*/
class BoxCollision {
public:
    /**
    * @brief �R���X�g���N�^
    */
    BoxCollision(GameObject& holder, const Math::OBB3D& obb);
    /**
    * @brief �f�X�g���N�^
    */
    ~BoxCollision();
    void setOBB(const Math::OBB3D& obb) { mOBB = obb; }
    Math::OBB3D* getOBB() { return &mOBB; }

    void calculateOBBFromTransform();
    void checkCollide(BoxCollision& other);
    void noticeCollide();
private:
    Math::OBB3D mOBB;
    GameObject& mHolder;
    std::vector<GameObject*> mHittedObjectList;
};

} //Main 