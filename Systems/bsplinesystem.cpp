#include "bsplinesystem.h"
#include "world.h"
#include "Components/bspline.h"
#include "Components/mesh.h"
#include "Factories/resourcefactory.h"

void BSplineSystem::beginPlay()
{
}

void BSplineSystem::tick(float /*deltaTime*/)
{
    for(auto const& entity : entities_)
    {
        auto spline = getWorld()->getComponent<BSpline>(entity).value();
        auto mesh = getWorld()->getComponent<Mesh>(entity).value();

        if(!spline->curve_.checkPathChanged()) return;

        Mesh m = ResourceFactory::get()->createLines(spline->curve_.getVerticesAndIndices());

        mesh->VAO_ = m.VAO_;
        mesh->verticeCount_ = m.verticeCount_;
        mesh->indiceCount_ = m.indiceCount_;
        mesh->drawType_ = m.drawType_;
        mesh->filepath_ = m.filepath_;
    }
}
