#include "pch.h"
#include "HermiteCurve.h"

#include <vector>

HermiteCurve::HermiteCurve(std::vector<Point3D> points) : mControlPoints(points)
{
}

HermiteCurve::~HermiteCurve()
{
}

std::vector<Point3D> HermiteCurve::calculateHermite()
{
    std::vector<Point3D> result;
    for (double t = 0; t <= 1; t += 0.001) {
        Point3D r = evaluateHermite(t);
        result.push_back(r);
    }
    return result;
}

Point3D HermiteCurve::evaluateHermite(double t)
{
    double t2 = t * t;
    double t3 = t2 * t;

    double blend1 = (2 * t3) - (3 * t2) + 1;
    double blend2 = (-2 * t3) + (3 * t2);
    double blend3 = t3 - (2 * t2) + t;
    double blend4 = t3 - t2;

    double x = blend1 * mControlPoints[0].x() + blend2 * (mControlPoints[1].x() - mControlPoints[0].x()) + blend3 * mControlPoints[2].x() + blend4 * (mControlPoints[3].x() - mControlPoints[2].x());
    double y = blend1 * mControlPoints[0].y() + blend2 * (mControlPoints[1].y() - mControlPoints[0].y()) + blend3 * mControlPoints[2].y() + blend4 * (mControlPoints[3].y() - mControlPoints[2].y());

    return Point3D(x, y);
}

