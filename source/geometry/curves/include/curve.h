#ifndef CURVE_H
#define CURVE_H

#include "mathlist.h"
#include "pointlist.h"

namespace tuco {

struct Curve
{
    Curve()
    {

    }
    virtual ~Curve()
    {

    }
    PointList* getPontList()
    {
        return pointlist;
    }
    virtual void setPointList(int _numNodes1) = 0;
protected:
    std::string name;
    Point* point1;
    Point* point2;
    PointList* pointlist;
};



struct Line : public Curve
{
    Line(Point* _point1, Point* _point2)
    {
        name = "line";
        pointlist = new PointList;
        point1 = _point1;
        point2 = _point2;

        length = (point2->r - point1->r).norm();
        cos = (point2->r - point1->r) / length;
    }
    ~Line()
    {

    }
    Vector3d getLine(double l)
    {
        Eigen::Vector3d r;
        r = l * cos + point1->r;
        return r;
    }
    virtual void setPointList(int _numNodes1) override
    {
        step1_ = length / (_numNodes1 - 1);

        for (int i = 0; i < _numNodes1; i++)
        {
            pointlist->setPoint(Point(i, point1->r + i * step1_ * cos));
        }
    }
private:
    double length;
    double step1_;
    Vector3d cos;
};

}



#endif // CURVE_H
