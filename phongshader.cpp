#include "phongshader.h"
#include "Components/material.h"
#include "Components/light.h"
#include "Components/transform.h"
#include "world.h"
PhongShader::PhongShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program, "mMatrix" );
    vMatrixUniform_ = glGetUniformLocation( program, "vMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program, "pMatrix" );

    //    textureUniform = glGetUniformLocation(program, "textureSampler");
    mLightColorUniform = glGetUniformLocation( program, "lightColor" );
    mObjectColorUniform = glGetUniformLocation( program, "objectColor" );
    mAmbientLightStrengthUniform = glGetUniformLocation( program, "ambientStrengt" );
    mLightPositionUniform = glGetUniformLocation( program, "lightPosition" );
    mSpecularStrengthUniform = glGetUniformLocation( program, "specularStrength" );
    mSpecularExponentUniform = glGetUniformLocation( program, "specularExponent" );
    mLightPowerUniform = glGetUniformLocation( program, "lightPower" );
    mCameraPositionUniform = glGetUniformLocation( program, "cameraPosition" );
}

PhongShader::~PhongShader()
{
    qDebug() << "Deleting PhongShader";
}

void PhongShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material)
{
    Shader::transmitUniformData(modelMatrix);

    if(!lightComponent || !lightTransformComponent)
        return;

    glUniform1f(mAmbientLightStrengthUniform, lightComponent->ambientStrength_);
    glUniform1f(mLightPowerUniform, lightComponent->lightStrength_);
    glUniform3f(mLightColorUniform, lightComponent->lightColor_.x, lightComponent->lightColor_.y, lightComponent->lightColor_.z);
    glUniform3f(mLightPositionUniform, lightTransformComponent->position_.x, lightTransformComponent->position_.y,lightTransformComponent->position_.z);
    glUniform3f(mObjectColorUniform, material->color_.x, material->color_.y, material->color_.z);
}

void PhongShader::setLight(Entity entity)
{
     lightComponent = getWorld()->getComponent<Light>(entity).value_or(nullptr);
     lightTransformComponent = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
}
