#ifndef GUI_H
#define GUI_H

#include "component.h"
#include "gltypes.h"
#include "GSL/vector2d.h"

struct GUI : public Component
{
    GUI();
    virtual QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;

    GLuint VAO_ = 0;
    gsl::Vector2D position_ = gsl::Vector2D(0);
    gsl::Vector2D scale_ = gsl::Vector2D(1);

};

#endif // GUI_H
