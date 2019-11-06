#include "bspline.h"
#include <QJsonArray>

BSpline::BSpline() {}

BSpline::~BSpline() {}

BSpline::BSpline(float speed, unsigned int degree)
{
    curve_.speed_ = speed;
    curve_.degree_ = degree;
}

QJsonObject BSpline::toJson()
{
    QJsonObject object;
    object.insert("speed", static_cast<double>(curve_.speed_));
    object.insert("degree", static_cast<int>(curve_.degree_));
    QJsonArray controlPoints;
    for (const auto& point : curve_.getControlPoints())
    {
        QJsonArray pointArray;
        pointArray.insert(0, QJsonValue(static_cast<double>(point.x)));
        pointArray.insert(1, QJsonValue(static_cast<double>(point.y)));
        pointArray.insert(2, QJsonValue(static_cast<double>(point.z)));
        controlPoints.push_back(pointArray);
    }
    object.insert("controlPoints", controlPoints);
    return object;
}

void BSpline::fromJson(QJsonObject Json)
{
    curve_ = BSplineCurve();
    curve_.speed_ = static_cast<float>(Json.take("speed").toDouble());
    curve_.degree_ = static_cast<unsigned int>(Json.take("degree").toInt());
    QJsonArray controlPoints = Json.take("controlPoints").toArray();
    for (const auto JsonPoint : controlPoints)
    {
        gsl::Vector3D point;
        point.x = static_cast<float>(JsonPoint.toArray().at(0).toDouble());
        point.y = static_cast<float>(JsonPoint.toArray().at(1).toDouble());
        point.z = static_cast<float>(JsonPoint.toArray().at(2).toDouble());
        curve_.addControlPoint(point);
    }
}
