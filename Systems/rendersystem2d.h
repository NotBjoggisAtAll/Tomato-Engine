#ifndef RENDERSYSTEM2D_H
#define RENDERSYSTEM2D_H

#include <QOpenGLFunctions_4_1_Core>
#include "system.h"


class RenderSystem2D :  public QOpenGLFunctions_4_1_Core, public System
{
public:
    RenderSystem2D();

    virtual void beginPlay() override;
    virtual void tick(float) override;
    virtual void endPlay() override;
    void setWidthAndHeight(int width, int height);

private:
    int width_ = 0;
    int height_ = 0;

};

#endif // RENDERSYSTEM2D_H
