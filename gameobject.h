#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Components/component.h"
#include "Components/meshcomponent.h"
#include "Components/materialcomponent.h"
#include "Components/transformcomponent.h"

enum DefaultObjectTypes
{
    E_Cube,
    E_Sphere,
    E_Plane,
    E_Monkey
};

class GameObject
{
public:
    virtual ~GameObject();

    static GameObject* Create(std::string Name);

    std::string mName;
    std::vector<Component*> mComponents;

    MeshComponent* mMeshComponent{nullptr};
    MaterialComponent* mMaterialComponent{nullptr};
    TransformComponent* mTransformComponent{nullptr};

private:
    GameObject();
};

#endif // GAMEOBJECT_H
