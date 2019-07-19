#include "CollisionManager.h"
#include "Utility/Debug.h"

namespace Main {
CollisionManager::CollisionManager() {
    mBoxCollisionList.clear();
}

CollisionManager::~CollisionManager() {
    mBoxCollisionList.clear();
}

void CollisionManager::update() {
    for (auto&& col : mBoxCollisionList) {
        col->calculateOBBFromTransform();
    }

    const int size = mBoxCollisionList.size();
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            mBoxCollisionList[i]->checkCollide(*mBoxCollisionList[j]);
        }
    }

    for (auto&& col : mBoxCollisionList) {
        col->noticeCollide();
    }
}

void CollisionManager::registerCollision(BoxCollision* collision) {
    MY_ASSERTION(collision, "ƒRƒŠƒWƒ‡ƒ“‚Énull‚ª“n‚³‚ê‚Ü‚µ‚½");
    mBoxCollisionList.emplace_back(collision);
}

} //Main 
