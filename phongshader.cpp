#include "phongshader.h"
#include "Components/materialcomponent.h"
#include "Components/lightcomponent.h"
#include "Components/transformcomponent.h"
#include "World.h"
PhongShader::PhongShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform = glGetUniformLocation( program, "mMatrix" );
    vMatrixUniform = glGetUniformLocation( program, "vMatrix" );
    pMatrixUniform = glGetUniformLocation( program, "pMatrix" );

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

    glUniform1f(mAmbientLightStrengthUniform, lightComponent->mAmbientStrenght);
    glUniform1f(mLightPowerUniform, lightComponent->mLightStrenght);
    glUniform3f(mLightColorUniform, lightComponent->mLightColor.x, lightComponent->mLightColor.y, lightComponent->mLightColor.z);
    glUniform3f(mLightPositionUniform, lightTransformComponent->position.x, lightTransformComponent->position.y,lightTransformComponent->position.z);
    glUniform3f(mObjectColorUniform, material->mColor.x, material->mColor.y, material->mColor.z);
}

void PhongShader::setLight(Entity entity)
{
     lightComponent = getWorld()->getComponent<Light>(entity).value_or(nullptr);
     lightTransformComponent = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
}
