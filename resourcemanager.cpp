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

TransformComponent* ResourceManager::getTransformComponent(Entity id)
{
    try {
        return &mTransformComponents.at(id);
    } catch (...) {
        if (mTransformMap.find(id) == mTransformMap.end())
            return nullptr;
        return &mTransformComponents.at(mTransformMap.at(id));
    }
}

MaterialComponent* ResourceManager::getMaterialComponent(Entity id)
{
    try {
        return &mMaterialComponents.at(id);
    } catch (...) {
        if (mMaterialMap.find(id) == mMaterialMap.end())
            return nullptr;
        return &mMaterialComponents.at(mMaterialMap.at(id));
    }
}

MeshComponent* ResourceManager::getMeshComponent(Entity id)
{
    try {
        return &mMeshComponents.at(id);
    } catch (...) {
        if (mMeshMap.find(id) == mMeshMap.end())
            return nullptr;
        else
            return &mMeshComponents.at(mMeshMap.find(id)->second);
    }
}
SoundComponent* ResourceManager::getSoundComponent(Entity id)
{
    try {
        return &mSoundComponents.at(id);
    } catch (...) {
        if (mSoundMap.find(id) == mSoundMap.end())
            return nullptr;
        return &mSoundComponents.at(mSoundMap.at(id));
    }
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
    auto Component = Factory->createMeshComponent(id,filePath,mMeshComponents);
    mMeshMap.insert(std::make_pair(id, mMeshComponents.size()-1));
    Component->EntityID = id;
    return Component;
}

SoundComponent *ResourceManager::createSoundComponent(Entity id, std::string filePath, bool loop, float gain)
{
    auto& Component = mSoundComponents.emplace_back(SoundComponent());
    mSoundMap.insert(std::make_pair(id, mSoundComponents.size()-1));
    Component.EntityID = id;
    Component.Sound = *SoundManager::instance()->createSource(filePath, {}, filePath, loop, gain);
    return &Component;
}
