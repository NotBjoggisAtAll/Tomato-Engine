#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Components/component.h"
#include "Components/materialcomponent.h"
#include "Components/transformcomponent.h"
class GameObject
{
public:
    virtual ~GameObject();

    GameObject(std::string Name);

    void addComponent(Component* component);

    std::string mName;
    std::vector<Component*> mComponents;

    MaterialComponent* mMaterialComponent;
    TransformComponent* mTransformComponent;


private:
};

#endif // GAMEOBJECT_H
