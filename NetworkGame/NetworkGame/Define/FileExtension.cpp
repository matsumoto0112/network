#include "FileExtension.h"
#include "Utility/Debug.h"

namespace Define {

const std::unordered_map<FileExtension, std::string> FileExtensionToStringConverter::mFileExtensionMap =
{
    {FileExtension::BMP,".bmp"},
    {FileExtension::JPG,".jpg"},
    {FileExtension::PNG,".png"},
    {FileExtension::CSO,".cso"},
};

const std::string& FileExtensionToStringConverter::convert(FileExtension extension) {
    auto item = mFileExtensionMap.find(extension);
    MY_ASSERTION(item != mFileExtensionMap.end(), "未登録の拡張子を変換しようとしました。");
    return item->second;
}

} //Define 