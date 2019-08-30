#include "gameobject.h"

GameObject::GameObject()
{
    mName = "GameObject";
    mComponents.reserve(11);
}

GameObject::~GameObject()
{

}
