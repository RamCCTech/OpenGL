#include "pch.h"
#include "BezierCurve.h"

#include <vector>

BezierCurve::BezierCurve(std::vector<Point3D> points) : mControlPoints(points)
{
}

BezierCurve::~BezierCurve()
{
}

std::vector<Point3D> BezierCurve::calculateBezier()
{
    std::vector<Point3D> result;
    for (double t = 0; t <= 1; t += 0.001) {
        Point3D r = evaluateBezier(t);
        result.push_back(r);
    }
    return result;
}

Point3D BezierCurve::evaluateBezier(double t)
{
    double u = 1.0 - t;
    double tt = t * t;
    double uu = u * u;
    double uuu = uu * u;
    double ttt = tt * t;

    double x = uuu * mControlPoints[0].x() + 3 * uu * t * mControlPoints[1].x() + 3 * u * tt * mControlPoints[2].x() + ttt * mControlPoints[3].x();
    double y = uuu * mControlPoints[0].y() + 3 * uu * t * mControlPoints[1].y() + 3 * u * tt * mControlPoints[2].y() + ttt * mControlPoints[3].y();
    Point3D p(x, y);

    return p;
}

