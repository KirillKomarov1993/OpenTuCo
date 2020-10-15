#ifndef POINTLIST_H
#define POINTLIST_H

#include "point.h"

namespace tuco {

struct PointList
{
    int numPoints;
    std::vector<Point> points;
    PointList()
    {
        numPoints = 0;
    }
    void setPoint(Point _point)
    {
        points.push_back(_point);
        numPoints++;
    }
    Point* getPoint(int _number)
    {
        for (auto &iPoint : points)
        {
            if (iPoint.number == _number) {
                return &iPoint;
            }
        }
    }
     std::vector<Point>* getPoints()
     {
         return &points;
     }
};

}

#endif // POINTLIST_H
