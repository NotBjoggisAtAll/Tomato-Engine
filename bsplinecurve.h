#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <vector>
#include "GSL/vector3d.h"

class Vertex;
class BSplineCurve
{
public:
    BSplineCurve(float speed, unsigned int degree = 2);

    void addControlPoint(gsl::Vector3D controlPoint);
    void removeControlPoint(gsl::Vector3D controlPoint);
    void randomizeControlpoints();

    gsl::Vector3D curvePosition();

    std::pair<std::vector<Vertex>, std::vector<unsigned int> > getVerticesAndIndices();

    ///Speed
    float speed_ = 0.1f;
    ///Degree
    unsigned int degree_ = 2;

    bool checkRandomized();

private:
    gsl::Vector3D evaluateBSpline(unsigned int nearestKnot, float x);

    ///knots
    std::vector<float> knots_;

    ///Control points
    std::vector<gsl::Vector3D> controlPoints_;

    void createKnots();
    unsigned int findKnotInterval(float x);

    float currentT_ = 0;
    bool bIncrementT = true;

    bool bRandomized_ = false;
};

#endif // BSPLINECURVE_H
