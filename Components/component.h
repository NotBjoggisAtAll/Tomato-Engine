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


struct Component
{
    Component();
     unsigned int EntityID{};
};



#endif // BASECOMPONENT_H
