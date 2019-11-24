#include "texturefactory.h"
#include "texture.h"

TextureFactory* TextureFactory::instance_ = nullptr;

TextureFactory *TextureFactory::get()
{
    if(!instance_)
        instance_ = new TextureFactory();
    return instance_;
}

GLuint TextureFactory::loadTexture(std::string file)
{
    auto textureIt = textureIDs_.find(file);
    if(textureIt != textureIDs_.end())
    {
        return textureIt->second;
    }
    Texture tex(file);
    textureIDs_.insert({file, tex.id()});
    return tex.id();
}
