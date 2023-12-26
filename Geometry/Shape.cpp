#include "pch.h"
#include "Shape.h"

Shape::Shape(const std::vector<Line>& polyLines)
    : mPolyLines(polyLines)
{
}

Shape::~Shape()
{
}

std::vector<Line>& Shape::getShape()
{
    return mPolyLines;
}

void Shape::setShape(std::vector<Line> vl)
{
    mPolyLines = vl;
}
void Shape::setShape(std::vector<Point3D> vp)
{
    mPoints = vp;
}

size_t Shape::getSize() const
{
    return mPolyLines.size();
}