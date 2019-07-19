#pragma once

#include <memory>
#include "Device/Graphics/Vertex/Vertex.h"
#include "Device/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Device/Graphics/Shader/VertexShader.h"
#include "Device/Graphics/Shader/PixelShader.h"
#include "Device/Graphics/Buffer/Constant/ConstantBufferManager.h"
#include "Device/Graphics/Texture/Texture.h"
#include "Device/Graphics/Buffer/Constant/MaterialCBufferStruct.h"
#include "Utility/Transform.h"

namespace Graphics {

/**
* @brief モデルの拡張子
*/
enum class ModelExtension {
    OBJ,
    FBX,
};

/**
* @struct Mesh
* @brief メッシュ管理クラス
*/
struct Mesh {
    std::unique_ptr<VertexAndIndexBuffer> mVIBuffer;
    std::shared_ptr<VertexShader> mVShader;
    std::shared_ptr<PixelShader> mPShader;
    int matIndex;
};

/**
* @struct Material
* @brief マテリアル管理クラス
*/
struct Material {
    std::string materialName; //!< マテリアル名
    Color4 ambient; //!< アンビエントカラー
    Color4 diffuse; //!< ディフューズカラー
    Color4 specular; //!< スペキュラーカラー
    float shininess; //!< Shininess
    float alpha; //!< アルファ値
    std::shared_ptr<Texture> mAmbientMap; //!< アンビエントマップ
    std::shared_ptr<Texture> mDiffuseMap; //!< ディフューズマップ
    std::shared_ptr<Texture> mSpecularMap; //!< スペキュラーマップ
    std::shared_ptr<Texture> mBumpMap; //!< バンプマップ
};

/**
* @class Model
* @brief モデル管理クラス
*/
class Model {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @param meshes メッシュリスト
    * @param materials マテリアルリスト
    */
    Model(GraphicsDeviceManager& graphicsDevice,
        std::vector<std::unique_ptr<Mesh>> meshes,
        std::vector<std::unique_ptr<Material>> materials);
    /**
    * @brief デストラクタ
    */
    virtual ~Model();
    /**
    * @brief 描画する
    */
    virtual void draw(const Transform& transform);
    void setVertexShader(std::shared_ptr<VertexShader> vshader, const std::vector<int>& indices = {});
    void setPixelShader(std::shared_ptr<PixelShader> pshader, const std::vector<int>& indices = {});
protected:
    GraphicsDeviceManager& mGraphicsDevice; //!< グラフィックデバイス
    std::vector<std::unique_ptr<Mesh>> mMeshes; //!< メッシュリスト
    std::vector<std::unique_ptr<Material>> mMaterials; //!< マテリアルリスト
};

} //Graphics 