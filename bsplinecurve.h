#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <vector>
#include "GSL/vector3d.h"

class Vertex;

/**
 * A class for making BSplines.
 */
class BSplineCurve
{
public:
    /**
      * Default constructor.
      */
    BSplineCurve() = default;
    /**
     * A constructor that takes in speed and a degree.
     * @param speed - float.
     * @param degree - unsigned int. Defaults to 2.
     */
    BSplineCurve(float speed, unsigned int degree = 2);

    /**
     * A constructor that takes in controlpoints, speed and a degree.
     * @param controlPoints - std::vector<gsl::Vector3D>.
     * @param speed - float.
     * @param degree - unsigned int. Defaults to 2.
     */
    BSplineCurve(std::vector<gsl::Vector3D> controlPoints, float speed, unsigned int degree = 2);

    /**
     * Adds a control point to the BSpline.
     * @param controlPoint - gsl::Vector3D.
     */
    void addControlPoint(gsl::Vector3D controlPoint);

    /**
     * Removes a control point from the BSpline.
     * @param controlPoint - gsl::Vector3D.
     */
    void removeControlPoint(gsl::Vector3D controlPoint);

    /**
     * Removes a control point from the BSpline.
     * @param index - unsigned int.
     */
    void removeControlPoint(unsigned int index);

    /**
     * Removes all controlpoints from the BSpline.
     */
    void removeControlPoints();

    /**
     * Randomizes the order of the controlpoints.
     * It does not include the first and the last point when randomizing.
     */
    void randomizeControlpoints();

    /**
     * Calculates the next position on the BSpline.
     * Based on t. A value between 0 and 1.
     * @return gsl::Vector3D with the next position on the BSpline.
     */
    gsl::Vector3D curvePosition(float t);

    /**
     * Calculates vertices and indces based on the control points.
     * Used for visualizing the curve and the controlpolygon.
     * @return std::pair<std::vector<Vertex, std::vector<unsigned int>>.
     */
    std::pair<std::vector<Vertex>, std::vector<unsigned int> > getVerticesAndIndices();

    /// The speed is used to calculate how fast to move across the BSpline.
    float speed_ = 0.1f;
    /// Which the degree the BSpline uses.
    unsigned int degree_ = 2;

    /**
     * Used to check if the path has changed.
    /// Mainly used for redrawing the curve and the controlpolygon after the controlPoints has been randomized by randomizeControlpoints().
     * @return boolean. True if the path has changed, otherwise returns false.
     */
    bool checkPathChanged();

    /**
     * Getter for control points.
     * @return std::vector<gsl::Vector3D>&. A refernce to the control points.
     */
    std::vector<gsl::Vector3D> &getControlPoints();

private:
    /**
     * Evaluates the BSpline at the current position (t).
     * @param nearestKnot The nearest knot to the current position.
     * @param t The current position on the BSpline.
     * @return gsl::Vector3D The current position in worldspace.
     */
    gsl::Vector3D evaluateBSpline(unsigned int nearestKnot, float t);

    /**
     * The control points of the BSpline.
     */
    std::vector<gsl::Vector3D> controlPoints_;

    /**
     * The knots calculated by createKnots().
     */
    std::vector<float> knots_;

    /**
     * Creates knots for the BSpline.
     */
    void createKnots();

    /**
     * Find the closest knot on the BSpline.
     * @param x The current position on the BSpline.
     * @return unsigned int. Returns the index of the closest knot.
     */
    unsigned int findKnotInterval(float x);

    /// Is set to true when the path is changed.
    bool bPathChanged = false;
};

#endif // BSPLINECURVE_H
