#include "resourcemanager.h"
#include "resourcefactory.h"

ResourceManager* ResourceManager::mInstance= nullptr;

ResourceManager::ResourceManager()
{

}

ResourceManager *ResourceManager::instance()
{
    if(!mInstance)
        mInstance = new ResourceManager();

    return mInstance;
}

TransformComponent *ResourceManager::createTransformComponent(unsigned int EntityID)
{
    auto& Component = mTransformComponents.emplace_back(TransformComponent());
    Component.EntityID = EntityID;
    return &Component;
}

MaterialComponent *ResourceManager::createMaterialComponent(unsigned int EntityID, Shader *Shader)
{
    auto& Component = mMaterialComponents.emplace_back(MaterialComponent());
    Component.EntityID = EntityID;
    Component.mShader = Shader;
    return &Component;
}

MeshComponent *ResourceManager::createMeshComponent(unsigned int EntityID, std::string filePath)
{
   return ResourceFactory::instance()->createMeshComponent(EntityID,filePath,mMeshComponents);
}
