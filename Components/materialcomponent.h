#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "GSL/vector3d.h"
#include <QJsonObject>
#include <QJsonArray>
#include "shader.h"
#include "Managers/shadermanager.h"

struct Material
{
    Material() = default;
    Material(Shader* Shader) : mShader(Shader), mColor(1,1,1) , mTextureUnit(0) {}
    Material(Shader* Shader, GLuint TextureUnit) : mShader(Shader), mColor(1,1,1), mTextureUnit(TextureUnit){}
    Material(Shader* Shader, gsl::Vector3D Color) : mShader(Shader), mColor(Color), mTextureUnit(0){}
    Material(Shader* Shader, gsl::Vector3D Color,  GLuint TextureUnit) : mShader(Shader), mColor(Color), mTextureUnit(TextureUnit){}
    Shader* mShader{nullptr};
    gsl::Vector3D mColor{1,1,1};
    GLuint mTextureUnit{0};

    Material(QJsonObject JSON)
    {
        std::string ShaderName = JSON.take("Shader Name").toString().toStdString();
        mShader = ShaderManager::instance()->getShader(ShaderName);
        QJsonArray colorArray = JSON.take("Color").toArray();
        mColor.x = static_cast<float>(colorArray.at(0).toDouble());
        mColor.y = static_cast<float>(colorArray.at(1).toDouble());
        mColor.z = static_cast<float>(colorArray.at(2).toDouble());
        mTextureUnit = static_cast<GLuint>(JSON.take("Textureunit").toInt());
    }
    QJsonObject toJSON()
    {
        QJsonObject Object;
        Object.insert("Shader Name", QString::fromStdString(mShader->mShaderName));
        QJsonArray colorArray;
        colorArray.insert(0, static_cast<double>(mColor.x));
        colorArray.insert(1, static_cast<double>(mColor.y));
        colorArray.insert(2, static_cast<double>(mColor.z));
        Object.insert("Color", colorArray);
        Object.insert("Textureunit", static_cast<int>(mTextureUnit));

        return Object;
    }
};

#endif // MATERIALCOMPONENT_H
