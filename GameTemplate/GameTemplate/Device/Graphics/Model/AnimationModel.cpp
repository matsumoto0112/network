#include "AnimationModel.h"
#include "Device/Graphics/Model/Bone.h"
#include "Device/Graphics/Model/Animation.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/Buffer/Constant/BoneMatrixCBufferStruct.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Model/Bone.h"

namespace Graphics {

AnimationModel::AnimationModel(GraphicsDeviceManager& graphicsDevice,
    std::vector<std::unique_ptr<Mesh>> meshes,
    std::vector<std::unique_ptr<Material>> materials,
    std::vector<std::unique_ptr<Bone>> bones,
    std::unique_ptr<Animation> animation)
    :Model(graphicsDevice, std::move(meshes), std::move(materials)),
    mBones(std::move(bones)), mAnimation(std::move(animation)),
    mCombMatrixArray(mBones.size()) {
    mAnimation->changeAnimation(0);
}

AnimationModel::~AnimationModel() {}

void AnimationModel::update(float delta) {
    mAnimation->update(delta);
}

void AnimationModel::draw(const Transform& transform) {
    const int size = mBones.size();
    for (int i = 0; i < size; i++) {
        mBones[i]->updateBoneMatrix(mAnimation->getAnimationMatrix(i));
        mBones[i]->inputMatrix(&mData.bone[i]);
    }

    ConstantBufferManager& cbManager = mGraphicsDevice.getConstantBufferManager();
    cbManager.setStruct(mData);
    Model::draw(transform);
}

} //Graphics 
