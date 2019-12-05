#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
/**
 * Contains relative paths to different folders containing assets for the game engine. Put all your assets inside these folders inorder to use them in the editor.
 */
namespace gsl  //Game School Lib
{
    const std::string projectFolderName{"../INNgine2019/"};
    const std::string assetFilePath{projectFolderName + "Assets/"};
    const std::string meshFilePath{projectFolderName + "Assets/Meshes/"};
    const std::string textureFilePath{projectFolderName + "Assets/Textures/"};
    const std::string soundFilePath{projectFolderName + "Assets/Sounds/"};
    const std::string jsonFilePath{projectFolderName + "Json/"};
    const std::string scriptFilePath{projectFolderName + "Assets/Scripts/"};
    const std::string shaderFilePath{projectFolderName + "Shaders/"};
}

#endif // CONSTANTS_H
