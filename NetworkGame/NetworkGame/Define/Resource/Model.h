#pragma once
#include <string>
namespace Define {

/**
* @enum ModelTYpe
* @brief description
*/
enum class ModelType {
    Floor,
    Enemy,
    Bullet,
    Object,
};

/**
* @class ModelName
* @brief discription
*/
class ModelName {
public:
    static const std::string FLOOR_NAME;
    static const std::string OBJECT_NAME;
    static const std::string ENEMY_NAME;
    static const std::string BULLET_NAME;
};

} //Define 