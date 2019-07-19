#include "RenderTargetManager.h"
#include "Utility/Debug.h"

namespace Graphics {

RenderTargetManager::RenderTargetManager(std::unique_ptr<RenderTarget> defaultRenderTarget) {
    mRenderTargets.emplace(0, std::move(defaultRenderTarget));
}
RenderTargetManager::~RenderTargetManager() {}

void RenderTargetManager::addRenderTarget(int id, std::unique_ptr<RenderTarget> renderTarget) {
    MY_ASSERTION(mRenderTargets.find(id) == mRenderTargets.end(),
        "“o˜^Ï‚İ‚ÌID‚ÅÄ“o˜^‚µ‚æ‚¤‚Æ‚µ‚Ü‚µ‚½B");
    mRenderTargets.emplace(id, std::move(renderTarget));
}

RenderTarget& RenderTargetManager::getRenderTarget(int id) {
    MY_ASSERTION(mRenderTargets.find(id) != mRenderTargets.end(),
        "–¢“o˜^‚ÌID‚ªŒÄ‚Î‚ê‚Ü‚µ‚½B");
    return *mRenderTargets[id];
}

void RenderTargetManager::setActiveRenderTarget(int id) {
    MY_ASSERTION(mRenderTargets.find(id) != mRenderTargets.end(),
        "–¢“o˜^‚ÌID‚ªŒÄ‚Î‚ê‚Ü‚µ‚½B");
    mRenderTargets[id]->activate();
}
} //Graphics 
