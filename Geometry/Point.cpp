#include "stdafx.h"
#include "Point.h"

Point::Point(double inX, double inY)
    :mX(0),
    mY(0)
{
    mX = inX;
    mY = inY;
}

Point::~Point()
{
}

double Point::x()
{
    return mX;
}

double Point::y()
{
    return mY;
}

void Point::setX(double x) {
    mX = x;
}

void Point::setY(double y) {
    mY = y;
}
