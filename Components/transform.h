#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "GSL/vector3d.h"

class QJsonObject;

struct Transform
{
    Transform() = default;
    Transform(gsl::Vector3D Position, gsl::Vector3D Rotation, gsl::Vector3D Scale);
    Transform(gsl::Vector3D Position);
    Transform(QJsonObject JSON);

    gsl::Vector3D position_{0,0,0};
    gsl::Vector3D rotation_{0,0,0};
    gsl::Vector3D scale_{1,1,1};

    QJsonObject toJson();

};

#endif // TRANSFORMCOMPONENT_H
