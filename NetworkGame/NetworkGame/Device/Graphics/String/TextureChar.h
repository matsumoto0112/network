
#include <memory>
#include "Device/Graphics/Sprite/Sprite2D.h"
#include "Utility/Math/IntVector2.h"

namespace Graphics {

/**
* @class TextureChar
* @brief �ꕶ�����̃e�N�X�`��
*/
class TextureChar : public Sprite2D {
    using IntVec2 = Math::IntVector2;
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param c �\������1����
    * @param fontSize �t�H���g�̑傫��
    * @param font �t�H���g�̎��
    */
    TextureChar(GraphicsDeviceManager& graphicsDevice, const char* c, int fontSize, const std::string& font);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~TextureChar();
    /**
    * @brief �`�悷��
    */
    virtual void draw() override;
    float getDisplayWidth() const;
    float getRightPositionX() const;
    Math::Vector2 getRightPosition() const;
private:
    IntVec2 mOffset;
    IntVec2 mBmpSize;
    IntVec2 mMargin;
};
} //Graphics 
