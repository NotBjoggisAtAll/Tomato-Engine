#include "texturefactory.h"
#include "texture.h"

TextureFactory* TextureFactory::instance_ = nullptr;

TextureFactory::TextureFactory()
{
}

TextureFactory *TextureFactory::get()
{
    if(!instance_)
        instance_ = new TextureFactory();
    return instance_;
}

GLuint TextureFactory::loadTexture(std::string file)
{
    Texture tex(file);
    return tex.id();
}
