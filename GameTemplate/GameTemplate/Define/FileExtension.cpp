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
    MY_ASSERTION(item != mFileExtensionMap.end(), "���o�^�̊g���q��ϊ����悤�Ƃ��܂����B");
    return item->second;
}

} //Define 