#include "shadermanager.h"

#include "colorshader.h"
#include "textureshader.h"
#include "phongshader.h"
ShaderManager* ShaderManager::m_Instance = nullptr;

ShaderManager* ShaderManager::instance()
{
    if(!m_Instance)
        m_Instance = new ShaderManager();
    return m_Instance;
}

PhongShader* ShaderManager::phongShader()
{
    return static_cast<PhongShader*>(mShaders.at(2));
}

TextureShader* ShaderManager::textureShader()
{
    return static_cast<TextureShader*>(mShaders.at(1));
}

ColorShader* ShaderManager::colorShader()
{
    return static_cast<ColorShader*>(mShaders.at(0));
}

ShaderManager::ShaderManager()
{
    //Compile shaders:
    mShaders.emplace_back(new ColorShader("plainshader"));
    mShaders.emplace_back(new TextureShader("textureshader"));
    mShaders.emplace_back(new PhongShader("phongshader"));
}

ShaderManager::~ShaderManager()
{
    delete m_Instance;
    m_Instance = nullptr;
}
