#ifndef BSPLINESYSTEM_H
#define BSPLINESYSTEM_H

#include "Systems/system.h"

class BSplineSystem : public System
{
public:
    BSplineSystem();
    virtual void beginPlay() override;
    virtual void tick() override;
};

#endif // BSPLINESYSTEM_H
