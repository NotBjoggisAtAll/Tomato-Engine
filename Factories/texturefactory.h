#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "gltypes.h"
#include <string>
class TextureFactory
{
public:

    static TextureFactory* get();
    /*
     * Binds and sends the texture to the GPU.
     * Returns the texture id.
     */
    GLuint loadTexture(std::string file);
private:
    TextureFactory();

    static TextureFactory* instance_;
};

#endif // TEXTUREFACTORY_H
