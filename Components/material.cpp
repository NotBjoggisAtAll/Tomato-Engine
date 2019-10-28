#include "material.h"
#include "shader.h"
#include <QJsonObject>
#include <QJsonArray>

Material::Material(Shader *Shader) : shader_(Shader), color_(1,1,1) , textureUnit_(0) {}

Material::Material(Shader *Shader, GLuint TextureUnit) : shader_(Shader), color_(1,1,1), textureUnit_(TextureUnit){}

Material::Material(Shader *Shader, gsl::Vector3D Color) : shader_(Shader), color_(Color), textureUnit_(0){}

Material::Material(Shader *Shader, gsl::Vector3D Color, GLuint TextureUnit) : shader_(Shader), color_(Color), textureUnit_(TextureUnit){}

Material::Material(QJsonObject JSON)
{
    std::string ShaderName = JSON.take("Shader Name").toString().toStdString();
    shader_ = ShaderManager::instance()->getShader(ShaderName);
    QJsonArray colorArray = JSON.take("Color").toArray();
    color_.x = static_cast<float>(colorArray.at(0).toDouble());
    color_.y = static_cast<float>(colorArray.at(1).toDouble());
    color_.z = static_cast<float>(colorArray.at(2).toDouble());
    textureUnit_ = static_cast<GLuint>(JSON.take("Textureunit").toInt());
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
    object.insert("Textureunit", static_cast<int>(textureUnit_));

    return object;
}
