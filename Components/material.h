#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "component.h"
#include "GSL/vector3d.h"

class Shader;

/**
 * A Component storing the Material data. Stores a pointer to the Shader. A color and a texture id.
 */
struct Material : public Component
{
    /**
     * Default constructor.
     */
    Material() = default;
    /**
     * A constructor taking in a pointer to a Shader.
     * @param Shader - Shader*. Usually uses a ShaderManager to get the pointer.
     */
    Material(Shader* Shader);

    /**
     * A constructor taking in a pointer to a Shader and the filepath to a Texture.
     * The Texture is made by the TexureFactory and the Textures ID is stored in this Component.
     * @param Shader - Shader*. Usually uses a ShaderManager to get the pointer.
     * @param Texture - std::string. The file containing the Texture. Needs to be stored in the Assets/Textures folder.
     */
    Material(Shader* Shader, std::string Texture);
    /**
     * A constructor taking in a pointer to a Shader and a color.
     * @param Shader - Shader*. Usually uses a ShaderManager to get the pointer.
     * @param Color
     */
    Material(Shader* Shader, gsl::Vector3D Color);
    Material(Shader* Shader, gsl::Vector3D Color,  std::string texture);

    /**
     * A constructor taking in a QJsonObject.
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject.
     */
    Material(QJsonObject Json);

    /**
     * Makes a QJsonObject containing the component data.
     * @return Returns a QJsonObject
     */
    QJsonObject toJson() override;
    /**
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    void fromJson(QJsonObject Json) override;

    /// A pointer to the Shader.
    Shader* shader_{nullptr};

    /// The Entity's color.
    gsl::Vector3D color_{1,1,1};

    /// The Texture's filepath. Used to load the Texture when loading a scene.
    std::string textureFile_ = "";

    /// The Texture's ID. Sent to the Gpu in order to find the correct Texture.
    GLuint textureUnit_{0};

};

#endif // MATERIALCOMPONENT_H
