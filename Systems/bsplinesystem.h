#ifndef BSPLINESYSTEM_H
#define BSPLINESYSTEM_H

#include "Systems/system.h"

class BSplineSystem : public System
{
public:
    BSplineSystem() = default;
    virtual void beginPlay() override;
    virtual void tick(float) override;
};

#endif // BSPLINESYSTEM_H
