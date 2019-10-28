#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "gltypes.h"
#include <string>

class QJsonObject;

struct Mesh
{

    Mesh() = default;
    Mesh(QJsonObject JSON);

    GLuint VAO_{0};
    GLuint verticeCount_{0};
    GLuint indiceCount_{0};
    GLenum drawType_{0};

    bool isVisible_{true};

    std::string filepath_ = "";

    QJsonObject toJson();
};

#endif // MESHCOMPONENT_H
