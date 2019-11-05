#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <string>
#include <unordered_map>

#include "colorshader.h"
#include "textureshader.h"
#include "phongshader.h"

class TextureShader;

class ShaderManager
{
public:
    static ShaderManager* instance();
    PhongShader *phongShader();
    TextureShader *textureShader();
    ColorShader *colorShader();

    Shader* getShader(std::string shaderName);
    //std::vector<Shader*> mShaders;
    std::unordered_map<std::string, Shader*> shaders_;
private:
    ShaderManager();
    ~ShaderManager();

    static ShaderManager* instance_;
};

#endif // SHADERMANAGER_H
