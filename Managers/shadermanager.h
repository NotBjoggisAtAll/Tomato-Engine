#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <string>
#include <unordered_map>

#include "plainshader.h"
#include "textureshader.h"
#include "phongshader.h"
#include "Shaders/colorshader.h"

class TextureShader;

class ShaderManager
{
public:
    static ShaderManager* instance();
    PhongShader *phongShader();
    TextureShader *textureShader();
    PlainShader *plainShader();
    ColorShader* colorShader();

    Shader* getShader(std::string shaderName);
    std::unordered_map<std::string, Shader*> shaders_;
private:
    ShaderManager();
    ~ShaderManager();

    static ShaderManager* instance_;
};

#endif // SHADERMANAGER_H
