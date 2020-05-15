#ifndef BSPLINE_H
#define BSPLINE_H

#include "component.h"
#include "bsplinecurve.h"

/**
 * A component wrapper for a BSplineCurve.
 */
struct BSpline : public Component
{
    /**
     * Default constructor.
     */
    BSpline() = default;

    /**
     * Constructor taking in a speed and a degree for the BSplineCurve.
     * @param speed - float
     * @param degree - unsigned int
     */
    BSpline(float speed, unsigned int degree = 2);

    /**
     * Default deconstructor.
     */
    virtual ~BSpline() override;

    /**
     * The actual BSplineCurve.
     */
    BSplineCurve curve_ = BSplineCurve(0.1f);

    /**
     * Makes a QJsonObject containing the component data.
     * @return Returns a QJsonObject
     */
    virtual QJsonObject toJson() override;

    /**
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    virtual void fromJson(QJsonObject Json) override;
};

#endif // BSPLINE_H
