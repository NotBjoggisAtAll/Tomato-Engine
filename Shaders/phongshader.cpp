#include "phongshader.h"
#include "Components/material.h"
#include "Components/light.h"
#include "Components/transform.h"
#include "world.h"

PhongShader::PhongShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program_, "mMatrix" );
    vMatrixUniform_ = glGetUniformLocation( program_, "vMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program_, "pMatrix" );

    lightColorUniform_ = glGetUniformLocation( program_, "lightColor" );
    objectColorUniform_ = glGetUniformLocation( program_, "objectColor" );
    ambientLightStrengthUniform_ = glGetUniformLocation( program_, "ambientStrengt" );
    lightPositionUniform_ = glGetUniformLocation( program_, "lightPosition" );
    specularStrengthUniform_ = glGetUniformLocation( program_, "specularStrength" );
    specularExponentUniform_ = glGetUniformLocation( program_, "specularExponent" );
    lightPowerUniform_ = glGetUniformLocation( program_, "lightPower" );
    cameraPositionUniform_ = glGetUniformLocation( program_, "cameraPosition" );
}

void PhongShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material)
{
    Shader::transmitUniformData(modelMatrix);

    if(!light_ || !lightTransform_)
        return;

    glUniform1f(ambientLightStrengthUniform_, light_->ambientStrength_);
    glUniform1f(lightPowerUniform_, light_->lightStrength_);
    glUniform3f(lightColorUniform_, light_->lightColor_.x, light_->lightColor_.y, light_->lightColor_.z);
    glUniform3f(lightPositionUniform_, lightTransform_->position_.x, lightTransform_->position_.y,lightTransform_->position_.z);
    glUniform3f(objectColorUniform_, material->color_.x, material->color_.y, material->color_.z);
}

void PhongShader::setLight(Entity entity)
{
    light_ = getWorld()->getComponent<Light>(entity).value_or(nullptr);
    lightTransform_ = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
}
