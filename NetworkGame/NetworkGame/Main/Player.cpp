#include "Player.h"
#include <iostream>
#include "Device/Graphics/Model/Model.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Device/GameDevice.h"
#include "Define/Resource/Model.h"
#include "Device/Input/InputManager.h"
#include "Device/Input/Keyboard.h"
#include "Utility/Resource/ResourceManager.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/Camera/FPSCamera.h"
#include "Utility/Console.h"
#include "Device/Input/Mouse.h"
#include "Device/Window/Window.h"
#include "Main/Bullet.h"
#include "Utility/Debug.h"
#include "Main/IBulletRegister.h"
#include "Main/ICollisionRegister.h"
#include "Main/BoxCollision.h"
#include "Define/Path.h"
#include "Utility/Resource/ResourceManager.h"

namespace Main {

Player::Player(IShooter& bulletRegister, ICollisionRegister& collisionRegister)
    :GameObject(Transform(Math::Vector3(0, 0.0f, 0), Math::Quaternion(), Math::Vector3(3.0f, 3.0f, 3.0f))),
    mBoxCollision(std::make_unique<BoxCollision>(*this, Math::OBB3D())),
    mPlayerCamera(Graphics::CameraManager::getInstance().getCamera<Graphics::FPSCamera>(Define::CameraType::ThreeD)),
    mBulletRegister(bulletRegister),
    mCollisionRegister(collisionRegister) {
    //長さを調整
    mBoxCollision->getOBB()->setLength(1, 2.0f);
    mCollisionRegister.registerCollision(mBoxCollision.get());

    mPlayer = Utility::ResourceManager::getInstance().getFBXModel()->getResource(Define::ModelType::Enemy);

    //カメラの座標を自身のモデルの目の付近に配置
    mPlayerCamera.setPosition(Math::Vector3(0, 4, 0), true);
}

Player::~Player() {}

const float speed = 0.2f;
const float rotSpeed = 5.0f;

void Player::update(float delta) {
    if (!Device::GameDevice::getInstance().getWindow().isActive())return;
    const Input::Keyboard& key = Device::GameDevice::getInstance().getInputManager().getKeyboard();
    Math::Vector3 move;
    if (key.getKey(Input::KeyCode::A)) {
        move.x--;
    }
    if (key.getKey(Input::KeyCode::D)) {
        move.x++;
    }
    if (key.getKey(Input::KeyCode::W)) {
        move.z++;
    }
    if (key.getKey(Input::KeyCode::S)) {
        move.z--;
    }
    move.normalize();

    const Input::Mouse& mouse = Device::GameDevice::getInstance().getInputManager().getMouse();
    Math::Vector2 mouseMove = mouse.getMove();
    if (mouse.getCursorMode() == Input::CursorMode::Show) {
        mouseMove = Math::Vector2::ZERO;
    }
    //カメラによる移動をした後にそれを用いて自分の場所を設定
    mPlayerCamera.calculatePositionAndRotation(move * speed, -mouseMove.x, mouseMove.y);
    mTransform.setPosition(mPlayerCamera.getPosition() - Math::Vector3(0, 4, 0));

    //カメラに合わせた回転
    Math::Quaternion rot;
    rot.setToRotateAboutY(Math::MathUtility::toRadian(mouseMove.x));
    mTransform.setRotate(mTransform.getRotate() * rot);

    if (mouse.getMouseDown(Input::MouseButton::Left)) {
        //向いている方向を取得する
        Math::Vector3 v = mPlayerCamera.getLookAt() - mPlayerCamera.getPosition();
        v.normalize();
        Math::Quaternion q = Math::Quaternion::createLookTarget(v.getNormal(), Math::Vector3::FORWORD);
        mBulletRegister.shoot(mPlayerCamera.getPosition(), q);
    }
}

void Player::draw() {
    mPlayer->draw(mTransform);
}

void Player::hit(GameObject& other) {}

} //Main 
