#pragma once

class Point
{
public:
    Point(double inX, double inY);
    ~Point();

    double x();
    double y();

    void setX(double x);
    void setY(double y);

private:
    double mX;
    double mY;
};