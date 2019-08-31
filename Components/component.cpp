#include "component.h"
Component *Component::Create(ComponentType Type)
{
    Component* ComponentToReturn = nullptr;
    switch (Type) {
    case E_Mesh:
        break;
    case E_Light:
        break;
    case E_Sound:
        break;
    case E_Camera:
        break;
    case E_Render:
        break;
    case E_Script:
        break;
    case E_Physics:
        break;
    case E_Material:
        break;
    case E_Collision:
        break;
    case E_Transform:
        break;
    }
    return ComponentToReturn;
}
