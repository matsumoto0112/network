#pragma once

#include <memory>
namespace Scene {

class IScene;

/**
* @class SceneManager
* @brief �V�[���Ǘ��N���X
*/
class SceneManager
{
public:
    /**
    * @brief �R���X�g���N�^
    * @param firstScene �ŏ��ɊJ���V�[��
    */
    SceneManager(std::unique_ptr<IScene> firstScene);
    /**
    * @brief �f�X�g���N�^
    */
    ~SceneManager();
    /**
    * @brief �X�V
    * @param delta �O�t���[������̍�������
    */
    void update(float delta);
    /**
    * @brief �`��
    */
    void draw();
private:
    std::unique_ptr<IScene> mCurrentScene; //!< ���݂̃V�[��
};

} //Scene 