#pragma once

#include "Utility/Math/Vector2.h"
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Vector4.h"
#include "Device/Graphics/Color4.h"

namespace Graphics {
/**
* @struct Vertex
* @brief ���_�\����
*/
struct Vertex {
    Math::Vector4 position; //!< ���W

    Vertex(float x, float y, float z, float w)
        :position(x, y, z, w) {}
    Vertex(const Math::Vector4& p)
        :position(p) {}
    Vertex()
        : position() {}
};

/**
* @struct SimpleVertex
* @brief ���_�ƐF���
*/
struct SimpleVertex : public Vertex {
    Color4 color; //!< �F���
    SimpleVertex(float x, float y, float z, float w, float r, float g, float b, float a)
        : Vertex(x, y, z, w), color(r, g, b, a) {}
    SimpleVertex(const Math::Vector4& v, const Color4& c)
        :Vertex(v), color(c) {}
    SimpleVertex()
        : Vertex(), color() {}
};

/**
* @struct TextureVertex
* @brief ���_�AUV���
*/
struct TextureVertex : public Vertex {
    float tex[2]; //!< UV���W
    TextureVertex(float x, float y, float z, float w, float u, float v)
        :Vertex(x, y, z, w), tex{ u,v }
    {}
    TextureVertex()
        :Vertex(), tex() {}
};

/**
* @struct TextureVertex3D
* @brief 3D�e�N�X�`�����蒸�_
*/
struct TextureVertex3D {
    Math::Vector4 pos; //!< ���W
    Math::Vector3 normal; //!< �@��
    Math::Vector2 uv; //!< UV���W

    TextureVertex3D() {};
    TextureVertex3D(const Math::Vector4& pos,
        const Math::Vector3& normal,
        const Math::Vector2& uv)
        :pos(pos), normal(normal), uv(uv) {};
};

/**
* @struct MeshVertex
* @brief ���b�V�����_
*/
struct MeshVertex {
    Math::Vector4 pos; //!< ���W
    Math::Vector3 normal; //!< �@��
    Math::Vector2 uv; //UV���W
    Color4 color; //!< ���_�J���[
};

struct AnimVert {
    Math::Vector4 pos;
    Math::Vector3 normal;
    Math::Vector2 uv;
    Color4 color;
    unsigned int index[4];
    float weight[4];
};

} //Graphics 
