#include "pch.h"
#include "SutherlandCohen.h"

#include <iostream>
#include <algorithm>
#include <limits>
#include <cfloat>

SutherlandCohen::SutherlandCohen(Shape region, Line l)
    : mRegion(region),
    mInputLine(l),
    mXMin(DBL_MAX),  // Initialize to the maximum possible value
    mXMax(std::numeric_limits<double>::lowest()),  // Initialize to the lowest possible value
    mYMin(DBL_MAX),
    mYMax(std::numeric_limits<double>::lowest())
{
    setRegion();
}

SutherlandCohen::~SutherlandCohen()
{}

Line SutherlandCohen::getClippedLine()
{
    // Compute region codes for P1, P2
    int code1 = computeCode(mInputLine.p1());
    int code2 = computeCode(mInputLine.p2());

    // Initialize line as outside the rectangular window
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2) {
            // If both endpoints are outside rectangle,
            // in same region
            break;
        }
        else {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = mInputLine.p1().y() + slope * (x - mInputLine.p1().x()),
            // x = mInputLine.p1().x() + (1 / slope) * (y - mInputLine.p1().y())
            if (code_out & TOP) {
                // point is above the clip rectangle
                x = mInputLine.p1().x() + (mInputLine.p2().x() - mInputLine.p1().x()) * (mYMax - mInputLine.p1().y()) / (mInputLine.p2().y() - mInputLine.p1().y());
                y = mYMax;
            }
            else if (code_out & BOTTOM) {
                // point is below the rectangle
                x = mInputLine.p1().x() + (mInputLine.p2().x() - mInputLine.p1().x()) * (mYMin - mInputLine.p1().y()) / (mInputLine.p2().y() - mInputLine.p1().y());
                y = mYMin;
            }
            else if (code_out & RIGHT) {
                // point is to the right of rectangle
                y = mInputLine.p1().y() + (mInputLine.p2().y() - mInputLine.p1().y()) * (mXMax - mInputLine.p1().x()) / (mInputLine.p2().x() - mInputLine.p1().x());
                x = mXMax;
            }
            else if (code_out & LEFT) {
                // point is to the left of rectangle
                y = mInputLine.p1().y() + (mInputLine.p2().y() - mInputLine.p1().y()) * (mXMin - mInputLine.p1().x()) / (mInputLine.p2().x() - mInputLine.p1().x());
                x = mXMin;
            }

            // Now intersection point x, y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1) {
                mInputLine.p1().setX(x);
                mInputLine.p1().setY(y);
                code1 = computeCode(mInputLine.p1());
            }
            else {
                mInputLine.p2().setX(x);
                mInputLine.p2().setY(y);
                code2 = computeCode(mInputLine.p2());
            }
        }
    }
    if (accept) {
        std::cout << "Line accepted from " << mInputLine.p1().x() << ", "
            << mInputLine.p1().y() << " to " << mInputLine.p2().x() << ", " << mInputLine.p2().y() << std::endl;

        Line l(mInputLine.p1(), mInputLine.p2());

        return l;
    }
    else {
        return mInputLine;
    }
}

void SutherlandCohen::setRegion()

{
    std::vector<Line> shape = mRegion.getShape();
    for (Line l : shape) {
        mXMin = min(l.p1().x(), mXMin);
        mXMin = min(l.p2().x(), mXMin);
        mYMin = min(l.p1().y(), mYMin);
        mYMin = min(l.p2().y(), mYMin);
        mXMax = max(l.p1().x(), mXMax);
        mXMax = max(l.p2().x(), mXMax);
        mYMax = max(l.p1().y(), mYMax);
        mYMax = max(l.p2().y(), mYMax);
    }
}

int SutherlandCohen::computeCode(Point3D p)
{
    // initialized as being inside
    int code = INSIDE;

    if (p.x() < mXMin) // to the left of rectangle
        code |= LEFT;
    else if (p.x() > mXMax) // to the right of rectangle
        code |= RIGHT;
    if (p.y() < mYMin) // below the rectangle
        code |= BOTTOM;
    else if (p.y() > mYMax) // above the rectangle
        code |= TOP;

    return code;
}

