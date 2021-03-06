#include "rendersystem2d.h"
#include "GSL/vector2d.h"
#include "GSL/matrix4x4.h"
#include "Components/gui.h"
#include "Components/material.h"
#include "world.h"
#include "Shaders/textureshader.h"
#include <array>

void RenderSystem2D::tick(float /*deltaTime*/)
{
    initializeOpenGLFunctions();

    for(const auto& entity : entities_)
    {
        GUI* gui = getWorld()->getComponent<GUI>(entity).value();
        Material* material = getWorld()->getComponent<Material>(entity).value();
        glUseProgram(material->shader_->getProgram());
        glBindVertexArray(gui->VAO_);

        gsl::Matrix4x4 modelMatrix;

        modelMatrix.setPosition(gui->position_.x,gui->position_.y,0);
        modelMatrix.scale((gui->scale_.x*height_)/width_, gui->scale_.y, 1.f);

        material->shader_->transmitUniformData(&modelMatrix, material);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
}

void RenderSystem2D::setWidthAndHeight(int width, int height)
{
    width_ = width;
    height_ = height;
}
