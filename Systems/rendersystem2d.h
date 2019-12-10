#ifndef RENDERSYSTEM2D_H
#define RENDERSYSTEM2D_H

#include <QOpenGLFunctions_4_1_Core>
#include "system.h"

/**
 * The RenderSystem is responsible to render 2D objects to the screen.
 */
class RenderSystem2D :  public QOpenGLFunctions_4_1_Core, public System
{
public:

    /**
     * Default constructor.
     */
    RenderSystem2D() = default;

    /**
     * Tick runs every frame.
     * Renders all GUI components based on their position.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    virtual void tick(float) override;

    /**
     * Used to update the width and height of the screen.
     * @param width - int.
     * @param height - int.
     */
    void setWidthAndHeight(int width, int height);

private:
    /// The screen's width.
    int width_ = 0;

    /// The screen's height.
    int height_ = 0;
};

#endif // RENDERSYSTEM2D_H
