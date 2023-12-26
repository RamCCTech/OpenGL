#pragma once
#include <vector>
#include "Line.h"

class GEOMETRY_API Shape
{
public:
    Shape(const std::vector<Line>& polyLines);
    ~Shape();

    std::vector<Line>& getShape();

    size_t getSize() const;
    void setShape(std::vector<Line> vl);
    void setShape(std::vector<Point3D> vp);

private:
    std::vector<Line> mPolyLines;
    std::vector<Point3D> mPoints;
};