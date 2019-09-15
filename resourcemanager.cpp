#include "resourcemanager.h"
#include "resourcefactory.h"
#include "Managers/soundmanager.h"
ResourceManager* ResourceManager::mInstance= nullptr;

ResourceManager::ResourceManager()
{
    Factory = new ResourceFactory();
}

ResourceManager::~ResourceManager()
{
    delete Factory;
    Factory = nullptr;
}

ResourceManager *ResourceManager::instance()
{
    if(!mInstance)
        mInstance = new ResourceManager();

    return mInstance;
}

TransformComponent *ResourceManager::createTransformComponent(Entity id)
{
    auto& Component = mTransformComponents.emplace_back(TransformComponent());
    mTransformMap.insert(std::make_pair(id, mTransformComponents.size()-1));
    Component.EntityID = id;
    return &Component;
}

MaterialComponent *ResourceManager::createMaterialComponent(Entity id, Shader *Shader)
{
    auto& Component = mMaterialComponents.emplace_back(MaterialComponent());
    mMaterialMap.insert(std::make_pair(id, mMaterialComponents.size()-1));
    Component.EntityID = id;
    Component.mShader = Shader;
    return &Component;
}

MeshComponent *ResourceManager::createMeshComponent(Entity id, std::string filePath)
{
    return Factory->createMeshComponent(id,filePath,mMeshComponents);
}

SoundComponent *ResourceManager::createSoundComponent(Entity id, std::string filePath, bool loop, float gain)
{
    auto& Component = mSoundComponents.emplace_back(SoundComponent());
    mSoundMap.insert(std::make_pair(id, mSoundComponents.size()-1));
    Component.EntityID = id;
    Component.Sound = *SoundManager::instance()->createSource(filePath, {}, filePath, loop, gain);
    return &Component;
}
