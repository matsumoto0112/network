#pragma once

#include "Utility/Math/Vector2.h"
#include "Utility/Math/Vector3.h"
#include "Utility/Math/Vector4.h"
#include "Device/Graphics/Color4.h"

namespace Graphics {
/**
* @struct Vertex
* @brief 頂点構造体
*/
struct Vertex {
    Math::Vector4 position; //!< 座標

    Vertex(float x, float y, float z, float w)
        :position(x, y, z, w) {}
    Vertex(const Math::Vector4& p)
        :position(p) {}
    Vertex()
        : position() {}
};

/**
* @struct SimpleVertex
* @brief 頂点と色情報
*/
struct SimpleVertex : public Vertex {
    Color4 color; //!< 色情報
    SimpleVertex(float x, float y, float z, float w, float r, float g, float b, float a)
        : Vertex(x, y, z, w), color(r, g, b, a) {}
    SimpleVertex(const Math::Vector4& v, const Color4& c)
        :Vertex(v), color(c) {}
    SimpleVertex()
        : Vertex(), color() {}
};

/**
* @struct TextureVertex
* @brief 頂点、UV情報
*/
struct TextureVertex : public Vertex {
    float tex[2]; //!< UV座標
    TextureVertex(float x, float y, float z, float w, float u, float v)
        :Vertex(x, y, z, w), tex{ u,v }
    {}
    TextureVertex()
        :Vertex(), tex() {}
};

/**
* @struct TextureVertex3D
* @brief 3Dテクスチャあり頂点
*/
struct TextureVertex3D {
    Math::Vector4 pos; //!< 座標
    Math::Vector3 normal; //!< 法線
    Math::Vector2 uv; //!< UV座標

    TextureVertex3D() {};
    TextureVertex3D(const Math::Vector4& pos,
        const Math::Vector3& normal,
        const Math::Vector2& uv)
        :pos(pos), normal(normal), uv(uv) {};
};

/**
* @struct MeshVertex
* @brief メッシュ頂点
*/
struct MeshVertex {
    Math::Vector4 pos; //!< 座標
    Math::Vector3 normal; //!< 法線
    Math::Vector2 uv; //UV座標
    Color4 color; //!< 頂点カラー
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
