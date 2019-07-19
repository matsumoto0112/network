#pragma once

namespace Main {

class BoxCollision;
/**
* @class ICollisionRegister
* @brief コリジョン追加インターフェース
*/
class ICollisionRegister {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~ICollisionRegister() = default;

   virtual void registerCollision(BoxCollision* collision) = 0;
};


} //Main 