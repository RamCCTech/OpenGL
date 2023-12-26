#pragma once
#include<Point3D.h>
#include<vector>
#include "pch.h"

class BEZIERCURVE_API BezierCurve
{
public:
	BezierCurve(std::vector<Point3D> points);
	~BezierCurve();
	std::vector<Point3D> calculateBezier();

private:
	Point3D evaluateBezier(double t);

private:
	std::vector<Point3D> mControlPoints;
};

