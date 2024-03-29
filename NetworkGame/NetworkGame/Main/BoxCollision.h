#pragma once
#include "Utility/Transform.h"
#include "Utility/Math/OBB3D.h"
#include <vector>

namespace Main {
class GameObject;
/**
* @class BoxCollision
* @brief ボックスのあたり判定
*/
class BoxCollision {
public:
    /**
    * @brief コンストラクタ
    */
    BoxCollision(GameObject& holder, const Math::OBB3D& obb);
    /**
    * @brief デストラクタ
    */
    ~BoxCollision();
    void setOBB(const Math::OBB3D& obb) { mOBB = obb; }
    Math::OBB3D* getOBB() { return &mOBB; }

    void calculateOBBFromTransform();
    void checkCollide(BoxCollision& other);
    void noticeCollide();
    void setColliderTransform(const Transform& transform) { mColliderTransform = transform; }
    const Transform& getColliderTransform() const { return mColliderTransform; }
private:
    Math::OBB3D mOBB;
    Transform mColliderTransform;
    GameObject& mHolder;
    std::vector<GameObject*> mHittedObjectList;
};

} //Main 