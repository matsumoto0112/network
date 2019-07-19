#include "FBXModelResourceStorage.h"
#include "Device/Graphics/Model/FBXLoader.h"
#include "Device/GameDevice.h"

namespace Utility {

Utility::FBXModelResourceStorage::FBXModelResourceStorage()
    :mFBXLoader(std::make_unique<Graphics::FBXLoader>(Device::GameDevice::getInstance().getDirectX11Device())) {}

Utility::FBXModelResourceStorage::~FBXModelResourceStorage() {}

void Utility::FBXModelResourceStorage::importResource(Define::ModelType type, const std::string& filepath) {
    if (exist(type))return;
    mResources.emplace(type, mFBXLoader->load(filepath));

}

} //Utility 
