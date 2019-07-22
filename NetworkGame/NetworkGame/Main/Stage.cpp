#include "Stage.h"
#include "Device/Graphics/Model/Model.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Device/GameDevice.h"
#include "Define/Resource/Model.h"
#include "Utility/Resource/ResourceManager.h"

#include "Device/Input/Mouse.h"
#include "Device/Input/InputManager.h"
#include "Define/Path.h"
#include "Main/Wall.h"
#include "Main/ICollisionRegister.h"
#include <iostream>

namespace Main {

Stage::Stage(ICollisionRegister& collisionRegister)
    :mFloorTransform(Math::Vector3(0, 0, 0), Math::Quaternion(), Math::Vector3(100.0f, 1.0f, 100.0f)),
    mObjectColor(Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f)),
    mFloorPlane(Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f)) {
    mFloor = Utility::ResourceManager::getInstance().getFBXModel()->getResource(Define::ModelType::Floor);

    mObjectModel = Utility::ResourceManager::getInstance().getFBXModel()->getResource(Define::ModelType::Object);
    Utility::PixelShaderResourceStorage* psManager = Utility::ResourceManager::getInstance().getPixelShader();
    mObjectModel->setPixelShader(psManager->getResource(Define::PixelShaderType::NoTextureNoLighting));

    mObjectTransforms.emplace_back(Math::Vector3(0.0f, 2.5f, 0.0f), Math::Quaternion(), Math::Vector3(1.0f, 1.0f, 1.0f));
    mObjectTransforms.emplace_back(Math::Vector3(5.0f, 2.5f, 0.0f), Math::Quaternion(), Math::Vector3(1.0f, 1.0f, 1.0f));

    Transform wallTransform(Math::Vector3(-100, 0, 0), Math::Quaternion(), Math::Vector3(1, 100, 100));
    mWalls[0] = std::make_unique<Wall>(wallTransform, collisionRegister);
    wallTransform = Transform(Math::Vector3(100, 0, 0), Math::Quaternion(), Math::Vector3(1, 100, 100));
    mWalls[1] = std::make_unique<Wall>(wallTransform, collisionRegister);
    wallTransform = Transform(Math::Vector3(0, 0, 100), Math::Quaternion(), Math::Vector3(100, 100, 1));
    mWalls[2] = std::make_unique<Wall>(wallTransform, collisionRegister);
    wallTransform = Transform(Math::Vector3(0, 0, -100), Math::Quaternion(), Math::Vector3(100, 100, 1));
    mWalls[3] = std::make_unique<Wall>(wallTransform, collisionRegister);
    wallTransform = Transform(Math::Vector3(0, 100, 0), Math::Quaternion(), Math::Vector3(100, 1, 100));
    mWalls[4] = std::make_unique<Wall>(wallTransform, collisionRegister);
    wallTransform = Transform(Math::Vector3(0, -100, 0), Math::Quaternion(), Math::Vector3(100, 1, 100));
    mWalls[5] = std::make_unique<Wall>(wallTransform, collisionRegister);
}


Stage::~Stage() {}

void Stage::update(float delta) {}

void Stage::draw() {
    mFloor->draw(mFloorTransform);
    Graphics::ConstantBufferManager& cbManager = Device::GameDevice::getInstance().getDirectX11Device().getConstantBufferManager();
    cbManager.setColor(Graphics::ConstantBufferParameterType::Color, mObjectColor);

    //オブジェクトの数分描画する
    for (auto&& tr : mObjectTransforms) {
        mObjectModel->draw(tr);
    }
}

} //Main 
