#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Components/basecomponent.h"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    std::string mName;
    std::vector<BaseComponent*> mComponents;
};

#endif // GAMEOBJECT_H
