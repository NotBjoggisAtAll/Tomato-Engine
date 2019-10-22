#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>
#include "system.h"

struct RenderSystem : public QOpenGLFunctions_4_1_Core, public System
{

    RenderSystem() = default;

     void beginPlay() override;
     void tick() override;
};

#endif // RENDERSYSTEM_H
