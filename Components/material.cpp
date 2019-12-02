#include "material.h"
#include "shader.h"
#include <QJsonObject>
#include <QJsonArray>
#include "Managers/shadermanager.h"
#include "Factories/texturefactory.h"

Material::Material(Shader *Shader) : shader_(Shader), color_(1,1,1) , textureUnit_(0) {}

Material::Material(Shader *Shader, std::string Texture) : shader_(Shader), color_(1,1,1), textureFile_(Texture)
{
    textureUnit_ = TextureFactory::get()->loadTexture(Texture);
}

Material::Material(Shader *Shader, gsl::Vector3D Color) : shader_(Shader), color_(Color){}

Material::Material(Shader *Shader, gsl::Vector3D Color, std::string texture) : shader_(Shader), color_(Color), textureFile_(texture)
{
    textureUnit_ = TextureFactory::get()->loadTexture(texture);
}

Material::Material(QJsonObject Json)
{
    fromJson(Json);
}

void Material::fromJson(QJsonObject Json)
{

    if(!Json.contains("Shader Name")) return;

    std::string ShaderName = Json.take("Shader Name").toString().toStdString();
    shader_ = ShaderManager::get()->getShader(ShaderName);
    QJsonArray colorArray = Json.take("Color").toArray();
    color_.x = static_cast<float>(colorArray.at(0).toDouble());
    color_.y = static_cast<float>(colorArray.at(1).toDouble());
    color_.z = static_cast<float>(colorArray.at(2).toDouble());
    textureFile_ = Json.take("texture file").toString().toStdString();
    if(textureFile_ != "")
        textureUnit_ = TextureFactory::get()->loadTexture(textureFile_);
}

QJsonObject Material::toJson()
{
    QJsonObject object;
    object.insert("Shader Name", QString::fromStdString(shader_->mShaderName));
    QJsonArray colorArray;
    colorArray.insert(0, static_cast<double>(color_.x));
    colorArray.insert(1, static_cast<double>(color_.y));
    colorArray.insert(2, static_cast<double>(color_.z));
    object.insert("Color", colorArray);
    object.insert("texture file", QString::fromStdString(textureFile_));
    return object;
}
