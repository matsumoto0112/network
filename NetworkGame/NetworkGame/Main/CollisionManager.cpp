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
    MY_ASSERTION(collision, "コリジョンにnullが渡されました");
    mBoxCollisionList.emplace_back(collision);
}

void CollisionManager::removeCollision(BoxCollision * collision) {
    MY_ASSERTION(collision, "コリジョンにnullが渡されました");
    auto removeIt = std::remove(mBoxCollisionList.begin(), mBoxCollisionList.end(), collision);
    mBoxCollisionList.erase(removeIt, mBoxCollisionList.end());
}

} //Main 
