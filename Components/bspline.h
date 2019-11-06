#ifndef BSPLINE_H
#define BSPLINE_H

#include "component.h"
#include "bsplinecurve.h"

struct BSpline : public Component
{
    BSpline();
    BSpline(float speed, unsigned int degree = 2);
    virtual ~BSpline() override;

    BSplineCurve curve_ = BSplineCurve(0.1f);

    virtual QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};

#endif // BSPLINE_H
