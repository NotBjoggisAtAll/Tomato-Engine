#ifndef BSPLINE_H
#define BSPLINE_H

#include "bsplinecurve.h"

struct BSpline
{
    BSpline();
    BSpline(float speed, unsigned int degree = 2);

    BSplineCurve curve_ = BSplineCurve(0.1f);
};

#endif // BSPLINE_H
