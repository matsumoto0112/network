#include "Viewport.h"

namespace Graphics {

Viewport::Viewport(const Math::Vector2& size) {
    //ビューポート作成
    mViewport.Width = size.x;
    mViewport.Height = size.y;
    mViewport.MinDepth = 0.0f;
    mViewport.MaxDepth = 1.0f;
    mViewport.TopLeftX = 0;
    mViewport.TopLeftY = 0;
}

Viewport::~Viewport() {}

Math::Vector2 Viewport::getSize() const {
    return Math::Vector2(mViewport.Width, mViewport.Height);
}

} //Graphics 
