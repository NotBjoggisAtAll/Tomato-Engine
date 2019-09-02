#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

enum ComponentType{
    E_Render,
    E_Camera,
    E_Collision,
    E_Light,
    E_Material,
    E_Mesh,
    E_Physics,
    E_Script,
    E_Sound,
    E_Transform
};

class GameObject;

struct Component
{
    static Component* Create(ComponentType Type);

    GameObject* Owner{nullptr};
};

#endif // BASECOMPONENT_H
