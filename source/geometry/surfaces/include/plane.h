#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

namespace tuco {

struct Plane : public Surface {
    Point point1;
    Point point2;
    Point point3;
    Plane(int _number, Point _point1, Point _point2, Point _point3) :
        Surface(_number), point1(_point1), point2(_point2), point3(_point3)
    {
        name = "plane";
        pointlist = new PointList;
        tangent1 = (_point2.r - _point1.r);
        tangent2 = (_point3.r - _point1.r);
    }
    void setPointList() override
        {
        //! Повернуть плоскость и растянуть (гомотетия)!!!
            mesh = new Mesh(name, "linear");
            pointlist = mesh->getCenters();
        }
    virtual void setPointList(int _numNodes1, int _numNodes2) override
    {
        step1_ = tangent1 / (_numNodes1 - 1);
        step2_ = tangent2 / (_numNodes2 - 1);

        for (int i = 0; i < _numNodes1; i++)
        {
            for (int j = 0; j < _numNodes2; j++)
            {
                pointlist->setPoint(Point(i*_numNodes1 + j, point1.r + i * step1_ +
                                                                      j * step2_));
            }
        }
    }
private:
    //int numNodes_;
    Vector3d step1_;
    Vector3d step2_;
};

}

#endif // PLANE_H
