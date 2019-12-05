#include "texturefactory.h"
#include "texture.h"
#include <QFile>
#include "constants.h"

TextureFactory* TextureFactory::instance_ = nullptr;

TextureFactory *TextureFactory::get()
{
    if(!instance_)
        instance_ = new TextureFactory();
    return instance_;
}

std::optional<GLuint> TextureFactory::loadTexture(std::string file)
{
    if(!QFile::exists(QString::fromStdString(gsl::textureFilePath) + QString::fromStdString(file)))
         return std::nullopt;

    auto textureIt = textureIDs_.find(file);
    if(textureIt != textureIDs_.end())
    {
        return textureIt->second;
    }
    Texture tex(file);
    textureIDs_.insert({file, tex.id()});
    return tex.id();
}
