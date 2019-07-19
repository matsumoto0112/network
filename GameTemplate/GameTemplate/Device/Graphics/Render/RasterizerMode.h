#pragma once

#include "Utility/HashCombine.h"

namespace Graphics {

/**
* @enum FillMode
* @brief �`�掞�̃t�B�����[�h�ݒ�
*/
enum class FillMode {
    Solid, //!< �ʓh��Ԃ�
    WireFrame, //!< ���C���[�t���[��
};

/**
* @enum CullMode
* @brief �J�����O���[�h�̐ݒ�
*/
enum class CullMode {
    Front, //!< �O�ʃJ�����O
    Back, //!< �w�ʃJ�����O
    None, //!< �J�����O�Ȃ�
};

/**
* @struct RasterizerMode
* @brief ���X�^���C�U�̐ݒ�\����
*/
struct RasterizerMode {
    CullMode mCullMode;
    FillMode mFillMode;

    /**
    * @brief �n�b�V���l
    */
    size_t getHash() const {
        size_t hash = 0;
        hash = Utility::combineHash(hash, mCullMode);
        hash = Utility::combineHash(hash, mFillMode);
        return hash;
    }
};

/**
* @struct RasterizerModeHash
* @brief �n�b�V���l�擾�p�֐��I�u�W�F�N�g
*/
struct RasterizerModeHash {
    size_t operator()(const RasterizerMode &r) const { return r.getHash(); }
};

/**
* @struct RasterizerModeEqual
* @brief  �������Z�p�֐��I�u�W�F�N�g
*/
struct RasterizerModeEqual {
    bool operator ()(const RasterizerMode& left, const RasterizerMode& right) const {
        return left.mCullMode == right.mCullMode &&left.mFillMode == right.mFillMode;
    }
};

} //Graphics 