#pragma once
#include <string>
#include <sstream>
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Quaternion.h"
#include "Utility/Debug.h"

namespace Network {

/**
* @enum DataType
* @brief パケットのデータの種類
*/
enum class DataType {
    Transform,
    Shot,
    Hit,
};

/**
* @class PacketDataBase
* @brief パケットデータエンコードインターフェース
*/
class IPacketDataEncoder {
public:
    virtual  ~IPacketDataEncoder() = default;
    virtual std::string encode() const = 0;
};

/**
* @class IPacketDataDecoder
* @brief パケットデータエンコードインターフェース
*/
class IPacketDataDecoder {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IPacketDataDecoder() = default;
    virtual void decode(const std::string& mes) = 0;
};

/**
* @class TransformData
* @brief プレイヤーの座標・回転のデータ群
*/
class TransformData : public IPacketDataEncoder, public IPacketDataDecoder {
public:
    Math::Vector3 position;
    Math::Quaternion rotate;
public:
    std::string encode() const override {
        std::stringstream ss;
        ss << (int)DataType::Transform << " ";
        ss << position.x << " " << position.y << " " << position.z << " ";
        ss << rotate.x << " " << rotate.y << " " << rotate.z << " " << rotate.w;
        return ss.str();
    }
    void decode(const std::string& mes) override {
        std::stringstream ss(mes);
        int type;
        ss >> type;
        MY_ASSERTION((DataType)type == DataType::Transform, "違う形式のデータが渡されました");
        ss >> position.x >> position.y >> position.z;
        ss >> rotate.x >> rotate.y >> rotate.z >> rotate.w;
    }
};

/**
* @class ShootData
* @brief プレイヤーのショットデータ群
*/
class ShootData : public IPacketDataEncoder, public IPacketDataDecoder {
public:
    Math::Vector3 shotPosition;
    Math::Quaternion rotate;
public:
    std::string encode() const override {
        std::stringstream ss;
        ss << (int)DataType::Shot << " ";
        ss << shotPosition.x << " " << shotPosition.y << " " << shotPosition.z << " ";
        ss << rotate.x << " " << rotate.y << " " << rotate.z << " " << rotate.w;
        return ss.str();
    }
    void decode(const std::string& mes) override {
        std::stringstream ss(mes);
        int type;
        ss >> type;
        MY_ASSERTION((DataType)type == DataType::Shot, "違う形式のデータが渡されました");
        ss >> shotPosition.x >> shotPosition.y >> shotPosition.z;
        ss >> rotate.x >> rotate.y >> rotate.z >> rotate.w;
    }
};

/**
* @class HitData
* @brief discription
*/
class HitData : public IPacketDataEncoder, public IPacketDataDecoder {
public:
    bool dead;
    int bulletID;
public:
    virtual std::string encode() const override {
        std::stringstream ss;
        ss << (int)DataType::Hit << " ";
        ss << dead << " " << bulletID;
        return ss.str();
    }

    virtual void decode(const std::string& mes) override {
        std::stringstream ss(mes);
        int type;
        ss >> type;
        MY_ASSERTION((DataType)type == DataType::Hit, "違う形式のデータが渡されました");
        ss >> dead >> bulletID;
    }
};

} //Network 