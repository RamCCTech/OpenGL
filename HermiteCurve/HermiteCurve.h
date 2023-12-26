#pragma once
#include<Point3D.h>
#include<vector>

#include "pch.h"

class HERMITECURVE_API HermiteCurve
{
public:
	HermiteCurve(std::vector<Point3D> points);
	~HermiteCurve();
	std::vector<Point3D> calculateHermite();
private:
	Point3D evaluateHermite(double t);
private:
	std::vector<Point3D> mControlPoints;
};

