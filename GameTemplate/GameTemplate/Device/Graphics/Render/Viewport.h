#pragma once

#include <d3d11.h>
#include "Utility/Math/Vector2.h"

namespace Graphics {

class Viewport {
public:
    Viewport(const Math::Vector2& size);
    ~Viewport();
    const D3D11_VIEWPORT& getViewport() const { return mViewport; }
    operator const D3D11_VIEWPORT* () const { return &mViewport; }
    Math::Vector2 getSize() const;
private:
    D3D11_VIEWPORT mViewport;
};

} //Graphics 