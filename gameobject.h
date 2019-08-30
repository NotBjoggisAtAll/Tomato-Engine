#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include "Components/basecomponent.h"

class GameObject : public QOpenGLFunctions_4_1_Core
{
public:
    GameObject();
    virtual ~GameObject();

    std::string mName;
    std::vector<BaseComponent*> mComponents;
};

#endif // GAMEOBJECT_H
