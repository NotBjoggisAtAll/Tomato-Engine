#include "bsplinecurve.h"
#include "vertex.h"

BSplineCurve::BSplineCurve(float speed, unsigned int degree) : speed_(speed), degree_(degree){}

gsl::Vector3D BSplineCurve::curvePosition()
{

    if(currentT_<0.01f)
    {
        bIncrementT = true;
        randomizeControlpoints();
    }
    if(currentT_>1)
    {
        bIncrementT = false;
        randomizeControlpoints();
    }
    if (bIncrementT)
        currentT_+=speed_/60;
    else
        currentT_-=speed_/60;

    return evaluateBSpline(findKnotInterval(currentT_),currentT_);
}

std::pair<std::vector<Vertex>,std::vector<unsigned int>> BSplineCurve::getVerticesAndIndices()
{
    std::vector<Vertex> curveVertices;
    std::vector<unsigned int> indices;

    for(const auto& pos : controlPoints_)
        curveVertices.push_back(Vertex(pos,{1,0,0},{}));

    for (float i = 0; i <= 1; i+= 0.01f)
        curveVertices.push_back(Vertex(evaluateBSpline(findKnotInterval(i),i), {0,1,0}, {}));

    for(unsigned int i = 0; i < curveVertices.size(); ++i)
    {
        if(i == controlPoints_.size()-1)
        {
            indices.push_back(i);
            indices.push_back(i+1);
            continue;
        }
        indices.push_back(i);
        if(i == 0) continue;
        indices.push_back(i);

    }
    return {curveVertices,indices};

}

bool BSplineCurve::checkPathChanged()
{
    if(bPathChanged)
    {
        bPathChanged = false;
        return true;
    }
    return false;
}

std::vector<gsl::Vector3D>& BSplineCurve::getControlPoints()
{
    return controlPoints_;
}

gsl::Vector3D BSplineCurve::evaluateBSpline(unsigned int nearestKnot, float t)
{
    gsl::Vector3D positionOnBSpline[20]; // forutsetter da at n+d+1 <= 20
    for (unsigned int j = 0; j <= degree_; j++)
    {
        positionOnBSpline[degree_ - j] = controlPoints_[nearestKnot - j];
    }

    for (unsigned int k = degree_; k > 0; k--)
    {
        unsigned int j = nearestKnot - k;
        for (unsigned int i = 0; i < k; i++)
        {
            j++;
            float w = (t - knots_[j]) / (knots_[j + k] - knots_[j]);
            positionOnBSpline[i] = positionOnBSpline[i] * (1 - w) + positionOnBSpline[i + 1] * w;
        }
    }
    return positionOnBSpline[0];
}

void BSplineCurve::createKnots()
{
    knots_.clear();
    unsigned int numberOfKnots = degree_ + static_cast<unsigned int>(controlPoints_.size()) + 1;
    unsigned int numberOfEndKnots = degree_ + 1;
    unsigned int numberOfMiddleKnots = numberOfKnots - (numberOfEndKnots * 2);

    for(unsigned int i = 1; i < numberOfKnots + 1; i++)
    {
        if(i <= degree_ + 1)
        {
            knots_.push_back(0);
            continue;
        }
        else if(i > numberOfKnots - (degree_ + 1))
        {
            knots_.push_back(1);
            continue;
        }
        else
        {
            float knot = 1 * (i - numberOfEndKnots);
            knot /= numberOfMiddleKnots + 1;
            knots_.push_back(knot);
            continue;
        }
    }
}

unsigned int BSplineCurve::findKnotInterval(float positionOnBSpline)
{
    unsigned int index = 0;
    for(unsigned int i = 0; i < knots_.size(); i++)
    {
        if(positionOnBSpline >= knots_[i])
            index = i;
    }
    return index;
}

void BSplineCurve::addControlPoint(gsl::Vector3D controlPoint)
{
    controlPoints_.push_back(controlPoint);
    createKnots();
    bPathChanged = true;
}

void BSplineCurve::removeControlPoint(gsl::Vector3D controlPoint)
{
    auto it = std::find(controlPoints_.begin(), controlPoints_.end(), controlPoint);
    controlPoints_.erase(it);
    createKnots();
    bPathChanged = true;
}

void BSplineCurve::randomizeControlpoints()
{
    std::random_shuffle(controlPoints_.begin() + 1, controlPoints_.end() - 1);
    bPathChanged = true;
}
