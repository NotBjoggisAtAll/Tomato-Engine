#include "gsl_math_extensions.h"

gsl::Vector2D gsle::map(gsl::Vector2D point, gsl::Vector2D oldMin, gsl::Vector2D oldMax, gsl::Vector2D newMin, gsl::Vector2D newMax)
{
    return gsl::Vector2D(
                (point.x-oldMin.x) * ((newMax.x - newMin.x)/(oldMax.x - oldMin.x))+ newMin.x,
                (point.y-oldMin.y) * ((newMax.y - newMin.y)/(oldMax.y - oldMin.y))+ newMin.y
                );
}
