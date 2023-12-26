#include "pch.h"
#include <vector>
#include <utility>
#include "Point3D.h"

class BSPLINECURVE_API BSplineCurve {
public:
	BSplineCurve(int degree);
	std::vector<Point3D> evaluate(std::vector<Point3D> control_points, float t);
private:
	int mDegree;
	std::vector<float> generateUniformKnots(int num_control_points);
	float bSplineBasis(int i, int k, float t, const std::vector<float>& knots);
};