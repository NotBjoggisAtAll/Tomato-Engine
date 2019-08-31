#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Components/component.h"

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
private:
    GameObject();
};

#endif // GAMEOBJECT_H
