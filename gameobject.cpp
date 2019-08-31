#include "gameobject.h"

GameObject::GameObject()
{
    mName = "GameObject";
    mComponents.reserve(11);
}

GameObject::~GameObject()
{

}

GameObject *GameObject::Create(std::string Name)
{
    GameObject* object = new GameObject();
    object->mName = Name;
    return object;
}
