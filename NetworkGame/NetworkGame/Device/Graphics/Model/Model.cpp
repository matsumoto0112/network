#include "Model.h"
#include <fstream>
#include <string>
#include "Define/Path.h"
#include "Device/GameDevice.h"
#include "Device/Graphics/GraphicsDeviceManager.h"
#include "Device/Graphics/Camera/CameraManager.h"
#include "Device/Graphics/Texture/TextureLoader.h"

namespace Graphics {

Model::Model(GraphicsDeviceManager& graphicsDevice,
    std::vector<std::unique_ptr<Mesh>> meshes,
    std::vector<std::unique_ptr<Material>> materials)
    :mGraphicsDevice(graphicsDevice),
    mMeshes(std::move(meshes)), mMaterials(std::move(materials)) {}

Model::~Model() {
    mMeshes.clear();
    mMaterials.clear();
}

void Model::draw(const Transform& transform) {
    ConstantBufferManager& cbManager = mGraphicsDevice.getConstantBufferManager();
    //座標変換行列の設定
    cbManager.setMatrix(Graphics::ConstantBufferParameterType::World, Math::Matrix4x4::transposition(transform.createSRTMatrix()));
    //メッシュをすべて描画
    for (auto&& mesh : mMeshes) {
        mesh->mVShader->set();
        mesh->mPShader->set();
        //マテリアル情報のセット
        cbManager.setColor(ConstantBufferParameterType::Ambient, mMaterials[mesh->matIndex]->ambient);
        cbManager.setColor(ConstantBufferParameterType::Diffuse, mMaterials[mesh->matIndex]->diffuse);
        cbManager.setColor(ConstantBufferParameterType::Specular, mMaterials[mesh->matIndex]->specular);
        cbManager.setFloat(ConstantBufferParameterType::Shininess, mMaterials[mesh->matIndex]->shininess);
        cbManager.setFloat(ConstantBufferParameterType::Alpha, mMaterials[mesh->matIndex]->alpha);

        //それぞれのテクスチャが存在すればセットする
        if (mMaterials[mesh->matIndex]->mAmbientMap != nullptr) {
            mMaterials[mesh->matIndex]->mAmbientMap->setData(ShaderInputType::Pixel, 1);
        }
        if (mMaterials[mesh->matIndex]->mDiffuseMap != nullptr) {
            mMaterials[mesh->matIndex]->mDiffuseMap->setData(ShaderInputType::Pixel, 2);
        }
        if (mMaterials[mesh->matIndex]->mSpecularMap != nullptr) {
            mMaterials[mesh->matIndex]->mSpecularMap->setData(ShaderInputType::Pixel, 3);
        }
        if (mMaterials[mesh->matIndex]->mBumpMap != nullptr) {
            mMaterials[mesh->matIndex]->mBumpMap->setData(ShaderInputType::Pixel, 4);
        }

        mesh->mVIBuffer->render();
    }
}

void Model::setVertexShader(std::shared_ptr<VertexShader> vshader, const std::vector<int>& indices) {
    //変更するメッシュのインデックスがあればそれを利用する
    if (indices.size() > 0) {
        for (auto&& i : indices) {
            mMeshes[i]->mVShader = vshader;
        }
        return;
    }
    //なければすべてのシェーダーを変える
    for (auto&& mesh : mMeshes) {
        mesh->mVShader = vshader;
    }
}

void Model::setPixelShader(std::shared_ptr<PixelShader> pshader, const std::vector<int>& indices) {
    //変更するメッシュのインデックスがあればそれを利用する
    if (indices.size() > 0) {
        for (auto&& i : indices) {
            mMeshes[i]->mPShader = pshader;
        }
        return;
    }
    //なければすべてのシェーダーを変える
    for (auto&& mesh : mMeshes) {
        mesh->mPShader = pshader;
    }
}

} //Graphics 
