#pragma once
#include <string>
#include <sstream>
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Quaternion.h"
#include "Utility/Debug.h"

namespace Network {

/**
* @enum DataType
* @brief �p�P�b�g�̃f�[�^�̎��
*/
enum class DataType {
    Transform,
    Shot,
};

/**
* @class PacketDataBase
* @brief discription
*/
class IPacketDataEncoder {
public:
    virtual  ~IPacketDataEncoder() = default;
    virtual std::string encode() const = 0;
};

/**
* @class IPacketDataDecoder
* @brief discription
*/
class IPacketDataDecoder {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IPacketDataDecoder() = default;
    virtual void decode(const std::string& mes) = 0;
};

/**
* @class TransformData
* @brief �v���C���[�̍��W�E��]�̃f�[�^�Q
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
        MY_ASSERTION((DataType)type == DataType::Transform, "�Ⴄ�`���̃f�[�^���n����܂���");
        ss >> position.x >> position.y >> position.z;
        ss >> rotate.x >> rotate.y >> rotate.z >> rotate.w;
    }
};

/**
* @class ShotData
* @brief �v���C���[�̃V���b�g�f�[�^�Q
*/
class ShotData : public IPacketDataEncoder, public IPacketDataDecoder {
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
        MY_ASSERTION((DataType)type == DataType::Shot, "�Ⴄ�`���̃f�[�^���n����܂���");
        ss >> shotPosition.x >> shotPosition.y >> shotPosition.z;
        ss >> rotate.x >> rotate.y >> rotate.z >> rotate.w;
    }
};

} //Network 