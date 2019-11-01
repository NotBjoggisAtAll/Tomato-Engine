#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <vector>
#include "GSL/vector3d.h"

class Vertex;
class BSplineCurve
{
public:
    BSplineCurve(float speed = 0.01f, unsigned int degree = 2);

    void addControlPoint(gsl::Vector3D controlPoint);
    void removeControlPoint(gsl::Vector3D controlPoint);

    gsl::Vector3D curvePosition();
    std::vector<Vertex> getCurveVertices();
    std::vector<Vertex> getControlVertices();
private:
    gsl::Vector3D evaluateBSpline(unsigned int nearestKnot, float x);
    unsigned int findKnotInterval(float x);
    void randomizeControlpoints();

    float speed_ = 0.01f;

    ///Degree
    unsigned int degrees_ = 2;
    ///knots
    std::vector<float> knots_;

    ///Control points
    std::vector<gsl::Vector3D> controlPoints_;

    void createKnots();

    float currentT_ = 0;
    bool bIncrementT = true;
};

#endif // BSPLINECURVE_H
