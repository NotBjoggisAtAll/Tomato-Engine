#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "gltypes.h"
#include <QJsonObject>
#include "resourcefactory.h"

struct Mesh
{
    Mesh(){}
    GLuint mVAO{0};

    GLuint mVerticeCount{0};
    GLuint mIndiceCount{0};
    GLenum mDrawType{0};

    bool isVisible{true};

    std::string filepath_ = "";

    Mesh(QJsonObject JSON)
    {
        *this = ResourceFactory::instance()->loadMesh(JSON.take("filepath").toString().toStdString()).first;
    }

    QJsonObject toJSON()
    {
        QJsonObject object;
        object.insert("visible", isVisible);
        object.insert("filepath", QString::fromStdString(filepath_));

        return object;
    }
};

#endif // MESHCOMPONENT_H
