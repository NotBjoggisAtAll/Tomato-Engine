#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "component.h"
#include "gltypes.h"
#include <string>

struct Mesh : public Component
{

    Mesh() = default;
    Mesh(QJsonObject Json);

    GLuint VAO_{0};
    GLuint verticeCount_{0};
    GLuint indiceCount_{0};
    GLenum drawType_{0};

    bool isVisible_{true};

    std::string filepath_ = "";

    QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};

#endif // MESHCOMPONENT_H
