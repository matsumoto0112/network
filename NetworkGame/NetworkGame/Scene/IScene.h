#pragma once

#include <memory>

namespace Scene {

/**
* @class IScene
* @brief �V�[���C���^�[�t�F�[�X
*/
class IScene
{
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IScene() = default;
    /**
    * @brief �X�V
    * @param delta �O�t���[������̍�������
    */
    virtual void update(float delta) = 0;
    /**
    * @brief �V�[�����I�����Ă��邩
    */
    virtual bool isEndScene() const = 0;
    /**
    * v�`��
    */
    virtual void draw() = 0;
    /**
    * @brief �V�[���̏I������
    * @return ���̃V�[��
    */
    virtual std::unique_ptr<IScene> end() = 0;
};

} //Scene 