#ifndef GSL_MATH_EXTENSIONS_H
#define GSL_MATH_EXTENSIONS_H

#include "vector2d.h"

namespace gsle
{
/**
 *
 * @param point - gsl::Vector2D.
 * @param oldMin
 * @param oldMax
 * @param newMin
 * @param newMax
 * @return
 */
gsl::Vector2D map(gsl::Vector2D point, gsl::Vector2D oldMin, gsl::Vector2D oldMax, gsl::Vector2D newMin, gsl::Vector2D newMax);
}

#endif // GSL_MATH_EXTENSIONS_H
