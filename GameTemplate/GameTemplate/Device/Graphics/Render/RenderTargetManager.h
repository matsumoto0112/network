#pragma once

#include <map>
#include <memory>
#include <d3d11.h>
#include "Device/Graphics/Render/RenderTarget.h"

namespace Graphics {

class RenderTargetView;

/**
* @class RenderTargetManager
* @brief レンダーターゲット管理
*/
class RenderTargetManager {
public:
    RenderTargetManager(std::unique_ptr<RenderTarget> defaultRenderTarget);
    ~RenderTargetManager();
    void addRenderTarget(int id, std::unique_ptr<RenderTarget> renderTarget);
    RenderTarget& getRenderTarget(int id);
    void setActiveRenderTarget(int num);
private:
    std::map<int, std::unique_ptr<RenderTarget>> mRenderTargets;
};

} //Graphics 