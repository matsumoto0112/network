#include "SceneManager.h"
#include "Scene/IScene.h"

namespace Scene {

SceneManager::SceneManager(std::unique_ptr<IScene> firstScene)
    :mCurrentScene(std::move(firstScene))
{}

SceneManager::~SceneManager()
{}

void SceneManager::update(float delta)
{
    mCurrentScene->update(delta);
    if (mCurrentScene->isEndScene())
    {
        mCurrentScene = mCurrentScene->end();
    }
}

void SceneManager::draw()
{
    mCurrentScene->draw();
}

} //Scene 
