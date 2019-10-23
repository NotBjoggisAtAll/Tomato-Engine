#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <string>
#include <unordered_map>

class TextureShader;
class Shader;
class PhongShader;
class ColorShader;


class ShaderManager
{
public:
    static ShaderManager* instance();
    PhongShader *phongShader();
    TextureShader *textureShader();
    ColorShader *colorShader();

    Shader* getShader(std::string shaderName);
    //std::vector<Shader*> mShaders;
    std::unordered_map<std::string, Shader*> mShaders;
private:
    ShaderManager();
    ~ShaderManager();

    static ShaderManager* m_Instance;
};

#endif // SHADERMANAGER_H
