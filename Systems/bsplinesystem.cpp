#include "bsplinesystem.h"
#include "world.h"
#include "Components/bspline.h"
#include "Components/mesh.h"
#include "Factories/resourcefactory.h"

BSplineSystem::BSplineSystem()
{

}

void BSplineSystem::beginPlay()
{
}

void BSplineSystem::tick(float deltaTime)
{
    for(auto const& entity : entities_)
    {
        auto spline = getWorld()->getComponent<BSpline>(entity).value_or(nullptr);
        auto mesh = getWorld()->getComponent<Mesh>(entity).value_or(nullptr);
        if(spline && mesh)
        {
            if(spline->curve_.checkPathChanged())
            {
                *mesh = ResourceFactory::get()->createLines(spline->curve_.getVerticesAndIndices());
            }
        }
    }
}
