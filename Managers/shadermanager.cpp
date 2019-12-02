#include "shadermanager.h"

ShaderManager* ShaderManager::instance_ = nullptr;

ShaderManager* ShaderManager::get()
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

PlainShader* ShaderManager::plainShader()
{
    return dynamic_cast<PlainShader*>(shaders_.at("plainshader"));
}

ColorShader *ShaderManager::colorShader()
{
    return dynamic_cast<ColorShader*>(shaders_.at("colorshader"));

}

GUIShader *ShaderManager::guiShader()
{
    return dynamic_cast<GUIShader*>(shaders_.at("guishader"));
}

Shader *ShaderManager::getShader(std::string shaderName)
{
    return shaders_.at(shaderName);
}

ShaderManager::ShaderManager()
{
    shaders_.insert(std::make_pair("plainshader", new PlainShader("plainshader")));
    shaders_.insert(std::make_pair("textureshader", new TextureShader("textureshader")));
    shaders_.insert(std::make_pair("phongshader", new PhongShader("phongshader")));
    shaders_.insert(std::make_pair("colorshader", new ColorShader("colorshader")));
    shaders_.insert(std::make_pair("guishader", new GUIShader("guishader")));
}

ShaderManager::~ShaderManager()
{
    for(const auto& shader : shaders_)
        delete shader.second;
    delete instance_;
    instance_ = nullptr;
}
