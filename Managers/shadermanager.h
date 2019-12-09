#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <string>
#include <unordered_map>

#include "Shaders/plainshader.h"
#include "Shaders/textureshader.h"
#include "Shaders/phongshader.h"
#include "Shaders/guishader.h"
#include "Shaders/colorshader.h"

class TextureShader;

/**
 * The ShaderManager is responsible for making and storing Shaders.
 * The Shader is read from files in the "Shaders" folder.
 */
class ShaderManager
{
public:

    /**
     * Singleton class.
     * @return A instance of the class.
     */
    static ShaderManager* get();

    /**
     * Getter for the PhongShader.
     * @return a pointer to PhongShader.
     */
    PhongShader *phongShader();

    /**
     * Getter for the TextureShader.
     * @return a pointer to TextureShader.
     */
    TextureShader *textureShader();

    /**
     * Getter for the PlainShader.
     * @return a pointer to PlainShader.
     */
    PlainShader *plainShader();

    /**
     * Getter for the ColorShader.
     * @return a pointer to ColorShader.
     */
    ColorShader* colorShader();

    /**
     * Getter for the GUIShader.
     * @return a pointer to GUIShader.
     */
    GUIShader* guiShader();

    /**
     * Getter for Shaders.
     * Assumes the shadername is valid.
     * @param shaderName - std::string.
     * @return a pointer to Shader.
     */
    Shader* getShader(std::string shaderName);

    /**
     * Getter for all Shaders.
     * @return a unordered_map with the Shaders.
     */
    std::unordered_map<std::string, Shader*> getShaders() const;
private:
    /// A unordered map with shaders where the shader name is the key and a Shader* is the value.
    std::unordered_map<std::string, Shader*> shaders_;

    /**
     * Default constructor. Since this is a singleton class the constructor is private.
     * Creates and stores the different shaders.
     */
    ShaderManager();

    /**
     * Default deconstructor. Deletes all the shaders.
     */
    ~ShaderManager();

    /// The singleton instance pointer.
    static ShaderManager* instance_;
};

#endif // SHADERMANAGER_H
