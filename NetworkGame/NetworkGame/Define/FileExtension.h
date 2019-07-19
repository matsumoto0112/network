#pragma once

#include <unordered_map>
#include <string>

namespace Define {

/**
* @enum FileExtension
* @brief ファイル拡張子列挙
*/
enum class FileExtension {
    BMP, //!< .bmp 
    PNG, //!< .png
    JPG, //!< .jpg
    CSO, //!< .cso
};

/**
* @class FileExtensionToStringConverter
* @brief ファイル拡張子を文字列に変換
*/
class FileExtensionToStringConverter {
public:
    /**
    * @brief 変換
    * @param extension ファイル拡張子
    * @return 変換した文字列
    */
    static const std::string& convert(FileExtension extension);
private:
    using FileExtensionMap = std::unordered_map<FileExtension, std::string>;
    static const FileExtensionMap mFileExtensionMap; //!< 拡張子と文字列のマップ
};
} //Define 
