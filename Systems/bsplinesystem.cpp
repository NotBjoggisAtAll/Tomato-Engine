#include "bsplinesystem.h"
#include "world.h"
#include "Components/bspline.h"
#include "Components/mesh.h"
#include "resourcefactory.h"

BSplineSystem::BSplineSystem()
{

}


void BSplineSystem::beginPlay()
{
}

void BSplineSystem::tick()
{
    for(auto Entity : entities_)
    {
        auto spline = getWorld()->getComponent<BSpline>(Entity).value_or(nullptr);
        if(spline)
        {
            if(spline->curve_.checkPathChanged())
            {
                getWorld()->removeComponent<Mesh>(Entity);
                getWorld()->addComponent(Entity, ResourceFactory::get()->createLines(spline->curve_.getVerticesAndIndices()));
            }
           // trans->position_ = spline->curve_.curvePosition();
        }
    }
}
