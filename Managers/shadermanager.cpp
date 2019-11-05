#include "shadermanager.h"

ShaderManager* ShaderManager::instance_ = nullptr;

ShaderManager* ShaderManager::instance()
{
    if(!instance_)
        instance_ = new ShaderManager();
    return instance_;
}

PhongShader* ShaderManager::phongShader()
{
    return dynamic_cast<PhongShader*>(shaders_.at("phongshader"));
}

TextureShader* ShaderManager::textureShader()
{
    return dynamic_cast<TextureShader*>(shaders_.at("textureshader"));
}

ColorShader* ShaderManager::colorShader()
{
    return dynamic_cast<ColorShader*>(shaders_.at("plainshader"));
}

Shader *ShaderManager::getShader(std::string shaderName)
{
    return shaders_.at(shaderName);
}

ShaderManager::ShaderManager()
{
    //Compile shaders:
    shaders_.insert(std::make_pair("plainshader", new ColorShader("plainshader")));
    shaders_.insert(std::make_pair("textureshader", new TextureShader("textureshader")));
    shaders_.insert(std::make_pair("phongshader", new PhongShader("phongshader")));
}

ShaderManager::~ShaderManager()
{
    delete instance_;
    instance_ = nullptr;
}
