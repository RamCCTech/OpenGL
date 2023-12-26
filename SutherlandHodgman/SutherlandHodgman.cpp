#include "pch.h"
#include "SutherlandHodgman.h"

SutherlandHodgman::SutherlandHodgman(Shape region, Shape polygon)
    : mRegion(region),
    mPolygon(polygon)
{
}

SutherlandHodgman::~SutherlandHodgman()
{
}

Shape SutherlandHodgman::getClippedPolygon()
{
    int size = mRegion.getSize();
    for (int i = 0; i < size; i++)
    {
        std::vector<Line> shape = mRegion.getShape();
        clipAlongLine(shape.at(i));
    }
    return Shape(mPolygon);
}


void SutherlandHodgman::clipAlongLine(Line l)
{
    std::vector<Point3D> newPoints;
    int newPolySize = 0;

    for (int i = 0; i < mPolygon.getSize(); i++)
    {

        Line& li = mPolygon.getShape().at(i);
        double i_pos = (l.p2().x() - l.p1().x()) * (li.p1().y() - l.p1().y()) - (l.p2().y() - l.p1().y()) * (li.p1().x() - l.p1().x());

        double k_pos = (l.p2().x() - l.p1().x()) * (li.p2().y() - l.p1().y()) - (l.p2().y() - l.p1().y()) * (li.p2().x() - l.p1().x());

        if (i_pos < 0 && k_pos < 0)
        {
            newPoints.push_back(li.p2());
            newPolySize++;
        }
        else if (i_pos >= 0 && k_pos < 0)
        {
            double x = xIntersect(l, li);
            double y = yIntersect(l, li);
            Point3D p(x, y);
            newPoints.push_back(p);
            newPolySize++;
            newPoints.push_back(li.p2());
            newPolySize++;
        }
        else if (i_pos < 0 && k_pos >= 0)
        {
            double x = xIntersect(l, li);
            double y = yIntersect(l, li);
            Point3D p(x, y);
            newPoints.push_back(p);
            newPolySize++;
        }
    }

    std::vector<Line> polyLine;

    for (int i = 0; i < newPolySize; i++)
    {
        polyLine.push_back(Line(newPoints.at(i), newPoints.at((i + 1) % newPoints.size())));
    }

    mPolygon.setShape(polyLine);
}

double SutherlandHodgman::xIntersect(Line l1, Line l2)
{
    double num = (l1.p1().x() * l1.p2().y() - l1.p1().y() * l1.p2().x()) * (l2.p1().x() - l2.p2().x()) - (l1.p1().x() - l1.p2().x()) * (l2.p1().x() * l2.p2().y() - l2.p1().y() * l2.p2().x());
    double den = (l1.p1().x() - l1.p2().x()) * (l2.p1().y() - l2.p2().y()) - (l1.p1().y() - l1.p2().y()) * (l2.p1().x() - l2.p2().x());
    return num / den;
}
double SutherlandHodgman::yIntersect(Line l1, Line l2)
{
    double num = (l1.p1().x() * l1.p2().y() - l1.p1().y() * l1.p2().x()) * (l2.p1().y() - l2.p2().y()) - (l1.p1().y() - l1.p2().y()) * (l2.p1().x() * l2.p2().y() - l2.p1().y() * l2.p2().x());
    double den = (l1.p1().x() - l1.p2().x()) * (l2.p1().y() - l2.p2().y()) - (l1.p1().y() - l1.p2().y()) * (l2.p1().x() - l2.p2().x());
    return num / den;
}