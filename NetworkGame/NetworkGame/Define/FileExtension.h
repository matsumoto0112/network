#pragma once

#include <unordered_map>
#include <string>

namespace Define {

/**
* @enum FileExtension
* @brief �t�@�C���g���q��
*/
enum class FileExtension {
    BMP, //!< .bmp 
    PNG, //!< .png
    JPG, //!< .jpg
    CSO, //!< .cso
};

/**
* @class FileExtensionToStringConverter
* @brief �t�@�C���g���q�𕶎���ɕϊ�
*/
class FileExtensionToStringConverter {
public:
    /**
    * @brief �ϊ�
    * @param extension �t�@�C���g���q
    * @return �ϊ�����������
    */
    static const std::string& convert(FileExtension extension);
private:
    using FileExtensionMap = std::unordered_map<FileExtension, std::string>;
    static const FileExtensionMap mFileExtensionMap; //!< �g���q�ƕ�����̃}�b�v
};
} //Define 
