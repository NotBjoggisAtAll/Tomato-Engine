#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "visualobject.h"
#include "vector3d.h"

class BillBoard : public VisualObject
{
public:
    BillBoard();

    virtual void init() override;
    virtual void draw() override;

    gsl::Vector3D getNormal();


    void setConstantYUp(bool constantUp);

private:
    gsl::Vector3D normal{0.f, 0.f, -1.f};

    bool mConstantYUp{true};
};

#endif // BILLBOARD_H
