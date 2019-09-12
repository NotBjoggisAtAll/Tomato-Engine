#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>

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
    std::vector<Shader*> mShaders;
private:
    ShaderManager();
    ~ShaderManager();

    static ShaderManager* m_Instance;
};

#endif // SHADERMANAGER_H
