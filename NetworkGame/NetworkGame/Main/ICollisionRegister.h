#pragma once

namespace Main {

class BoxCollision;
/**
* @class ICollisionRegister
* @brief �R���W�����ǉ��C���^�[�t�F�[�X
*/
class ICollisionRegister {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ICollisionRegister() = default;

   virtual void registerCollision(BoxCollision* collision) = 0;
};


} //Main 