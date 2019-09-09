#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Components/allcomponents.h"

class ResourceManager
{
public:
    static ResourceManager* instance();

    TransformComponent *createTransformComponent(unsigned int EntityID);
    MaterialComponent *createMaterialComponent(unsigned int EntityID, Shader *Shader);
    MeshComponent *createMeshComponent(unsigned int EntityID, std::string filePath);

     std::vector<TransformComponent> mTransformComponents;
     std::vector<MaterialComponent> mMaterialComponents;
     std::vector<MeshComponent> mMeshComponents;

private:
    ResourceManager();

    static ResourceManager* mInstance;

};

#endif // RESOURCEMANAGER_H
