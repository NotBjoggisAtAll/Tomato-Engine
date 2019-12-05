#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "gltypes.h"
#include <string>
#include <unordered_map>
#include <optional>

/**
 * Responsible for loading and storing textures.
 */
class TextureFactory
{
public:

    /**
     * Singleton class.
     * @return A instance of the class.
     */
    static TextureFactory* get();

    /**
     * Binds and sends the texture to the GPU.
     * Returns the texture id.
     */
    /**
     * Binds and sends the texture to the GPU.
     * Stores the texture loaded for later use.
     * If the file doesnt exist returns a nullopt.
     * @param file - std::string. The texture you want to load. Needs to be in the Assets/Textures folder.
     * @return The texture ID in a std::optional.
     */
    std::optional<GLuint> loadTexture(std::string file);
private:
    /**
     * Default Constructor. Since this is a singleton class the constructor is private.
     */
    TextureFactory() = default;

    /// The map is used to store texture ids.
    std::unordered_map<std::string, GLuint> textureIDs_;

    /// The singleton instance pointer.
    static TextureFactory* instance_;
};

#endif // TEXTUREFACTORY_H
