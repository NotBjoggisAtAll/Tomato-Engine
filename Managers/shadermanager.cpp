#include "shadermanager.h"

ShaderManager* ShaderManager::m_Instance = nullptr;

ShaderManager* ShaderManager::instance()
{
    if(!m_Instance)
        m_Instance = new ShaderManager();
    return m_Instance;
}

PhongShader* ShaderManager::phongShader()
{
    return dynamic_cast<PhongShader*>(mShaders.at("phongshader"));
}

TextureShader* ShaderManager::textureShader()
{
    return dynamic_cast<TextureShader*>(mShaders.at("textureshader"));
}

ColorShader* ShaderManager::colorShader()
{
    return dynamic_cast<ColorShader*>(mShaders.at("plainshader"));
}

Shader *ShaderManager::getShader(std::string shaderName)
{
    return mShaders.at(shaderName);
}

ShaderManager::ShaderManager()
{
    //Compile shaders:
    mShaders.insert(std::make_pair("plainshader", new ColorShader("plainshader")));
    mShaders.insert(std::make_pair("textureshader", new TextureShader("textureshader")));
    mShaders.insert(std::make_pair("phongshader", new PhongShader("phongshader")));
}

ShaderManager::~ShaderManager()
{
    delete m_Instance;
    m_Instance = nullptr;
}
