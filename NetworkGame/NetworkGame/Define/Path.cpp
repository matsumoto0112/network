#include "Path.h"
#include <Windows.h>
#include <iostream>
#include "Utility/Debug.h"

namespace {
constexpr int MAX_SIZE = 1024;

std::string getExePath() {
    char path[MAX_SIZE];
    DWORD ret = GetModuleFileName(nullptr, path, sizeof(path));
    std::string res(path);
    return res;
}
}

namespace Define {
Path::Path() {
    mExe = getExePath();
    std::cout << ".exe path:" << mExe << "\n";
    char dir[MAX_SIZE];
    char drive[MAX_SIZE];
    char name[MAX_SIZE];
    char ext[MAX_SIZE];

    _splitpath_s(&mExe[0], drive, sizeof(drive), dir, sizeof(dir), name, sizeof(name), ext, sizeof(ext));
    std::string sDir(drive);
    sDir += dir;
    std::string::size_type pos = sDir.find_last_of("\\/");
    sDir = sDir.substr(0, pos);

    mShader = sDir + "/cso/";
    mResource = sDir + "/Resources/";
    mModel = mResource + "Model/";
    mFBXModel = mModel + "FBX/";
    mTexture = mResource + "/Textures/";
}

Path::~Path() {}

} //Define 