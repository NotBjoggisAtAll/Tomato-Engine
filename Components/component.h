#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

enum class ComponentType{
    Render,
    Camera,
    Collision,
    Light,
    Material,
    Mesh,
    Physics,
    Script,
    Sound,
    Transform
};

class GameObject;

struct Component
{
    static Component* Create(ComponentType Type);

    GameObject* Owner{nullptr}; //TODO remove

     unsigned int EntityID{};
};



#endif // BASECOMPONENT_H
