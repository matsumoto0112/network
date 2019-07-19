#include "Animation.h"
#include "Utility/Debug.h"
#include "Device/Graphics/Model/Motion.h"

Graphics::Animation::Animation()
    :mCurrentMotion(0) {}

Graphics::Animation::~Animation() {}

void Graphics::Animation::addMotion(int id, std::unique_ptr<Motion> motion) {
    mMotions.emplace(id, std::move(motion));
}

void Graphics::Animation::update(float delta) {
    MY_ASSERTION(mMotions.find(mCurrentMotion) != mMotions.end(),
        "存在しないモーションが呼ばれました");

    mTime += delta;
    const int curMotionFrameNum = mMotions[mCurrentMotion]->getKeyFrameNum();
    if (mTime >= curMotionFrameNum) {
        mTime -= curMotionFrameNum;
    }
}

void Graphics::Animation::changeAnimation(int id) {
    MY_ASSERTION(mMotions.find(mCurrentMotion) != mMotions.end(),
        "存在しないモーションが呼ばれました");
    mCurrentMotion = id;
    mTime = 0.0f;
}

Math::Matrix4x4 Graphics::Animation::getAnimationMatrix(int bone) {
    int frame = (int)mTime;
    Math::Matrix4x4 mat1 = mMotions[mCurrentMotion]->getKeyFrame(frame, bone);
    const int curMotionFrameNum = mMotions[mCurrentMotion]->getKeyFrameNum();
    Math::Matrix4x4 mat2 = mMotions[mCurrentMotion]->getKeyFrame((frame + 1) % curMotionFrameNum, bone);

    return Math::Matrix4x4::lerp(mat1, mat2, mTime - frame);
}
