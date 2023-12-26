#include "pch.h"
#include "Line.h"

Line::Line(Point3D p1, Point3D p2)
    : mP1(p1),
    mP2(p2)
{
}
Line::Line(const Line& other)
    : mP1(other.mP1),
    mP2(other.mP2)
{
    // You may need to copy other necessary data members if any
}

Line::~Line()
{
}

Point3D& Line::p1()
{
    return mP1;
}

Point3D& Line::p2()
{
    return mP2;
}

Line& Line::operator=(const Line& other)
{
    if (this != &other)  // Check for self-assignment
    {
        // Copy data members from 'other' to 'this'
        mP1 = other.mP1;
        mP2 = other.mP2;
    }
    return *this;
}