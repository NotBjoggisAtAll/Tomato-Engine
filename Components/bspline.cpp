#include "bspline.h"

BSpline::BSpline()
{

}

BSpline::BSpline(float speed, unsigned int degree)
{
    curve_.speed_ = speed;
    curve_.degree_ = degree;
}