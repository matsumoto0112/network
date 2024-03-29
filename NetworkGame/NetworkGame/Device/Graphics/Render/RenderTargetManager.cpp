#include "RenderTargetManager.h"
#include "Utility/Debug.h"

namespace Graphics {

RenderTargetManager::RenderTargetManager(std::unique_ptr<RenderTarget> defaultRenderTarget) {
    mRenderTargets.emplace(0, std::move(defaultRenderTarget));
}
RenderTargetManager::~RenderTargetManager() {}

void RenderTargetManager::addRenderTarget(int id, std::unique_ptr<RenderTarget> renderTarget) {
    MY_ASSERTION(mRenderTargets.find(id) == mRenderTargets.end(),
        "登録済みのIDで再登録しようとしました。");
    mRenderTargets.emplace(id, std::move(renderTarget));
}

RenderTarget& RenderTargetManager::getRenderTarget(int id) {
    MY_ASSERTION(mRenderTargets.find(id) != mRenderTargets.end(),
        "未登録のIDが呼ばれました。");
    return *mRenderTargets[id];
}

void RenderTargetManager::setActiveRenderTarget(int id) {
    MY_ASSERTION(mRenderTargets.find(id) != mRenderTargets.end(),
        "未登録のIDが呼ばれました。");
    mRenderTargets[id]->activate();
}
} //Graphics 
