#pragma once
#include "Utility/Math/OBB3D.h"
#include "Device/Graphics/Primitive/PrimitiveBase.h"

namespace Graphics {

/**
* @class OBB3D
* @brief OBB3D�v���~�e�B�u�`��N���X
*/
class OBB3D : public PrimitiveBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    OBB3D(GraphicsDeviceManager& graphicsDevice, const Math::OBB3D& obb);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~OBB3D();
    const Math::OBB3D& getOBB() const { return mOBB; }
private:
    Math::OBB3D mOBB;
};

} //Graphics 