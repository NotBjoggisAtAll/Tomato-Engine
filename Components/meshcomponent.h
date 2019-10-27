#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "gltypes.h"
#include <QJsonObject>

struct Mesh
{
    Mesh(){}
    GLuint mVAO{0};

    GLuint mVerticeCount{0};
    GLuint mIndiceCount{0};
    GLenum mDrawType{0};

    bool isVisible{true};

    std::string filepath_ = "";

    Mesh(QJsonObject JSON);

    QJsonObject toJSON();
};

#endif // MESHCOMPONENT_H
