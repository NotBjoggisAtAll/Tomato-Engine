#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Components/allcomponents.h"
#include "Entity.h"
#include <unordered_map>

class ResourceFactory;

typedef unsigned int ComponentID;

class ResourceManager
{
public:
    static ResourceManager* instance();

    TransformComponent *createTransformComponent(Entity id);
    MaterialComponent *createMaterialComponent(Entity id, Shader *Shader);
    MeshComponent *createMeshComponent(Entity id, std::string filePath);
    SoundComponent* createSoundComponent(Entity id, std::string filePath, bool loop, float gain);
    //Stores where in the vector the component for each entity is
    std::unordered_map<Entity, ComponentID> mTransformMap;
    std::unordered_map<Entity, ComponentID> mMaterialMap;
    std::unordered_map<Entity, ComponentID> mMeshMap;
    std::unordered_map<Entity, ComponentID> mSoundMap;


    std::vector<TransformComponent> mTransformComponents;
    std::vector<MaterialComponent> mMaterialComponents;
    std::vector<MeshComponent> mMeshComponents;
    std::vector<SoundComponent> mSoundComponents;

    TransformComponent *getTransformComponent(Entity id);
    MaterialComponent *getMaterialComponent(Entity id);
    MeshComponent *getMeshComponent(Entity id);
    SoundComponent *getSoundComponent(Entity id);
private:
    ResourceManager();
    ~ResourceManager();

    ResourceFactory* Factory{nullptr};

    static ResourceManager* mInstance;

};

#endif // RESOURCEMANAGER_H
