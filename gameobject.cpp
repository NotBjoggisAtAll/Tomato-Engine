#include "gameobject.h"

GameObject::GameObject(std::string Name) : mName(Name)
{
    mComponents.reserve(11);
}

GameObject::~GameObject()
{

}

void GameObject::addComponent(Component *component)
{
    component->Owner = this;
    mComponents.push_back(component);
}
