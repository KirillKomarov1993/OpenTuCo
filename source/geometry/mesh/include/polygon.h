#ifndef POLYGON_H
#define POLYGON_H

//#include "space/pointlist.h"
#include "mathlist.h"
#include "point.h"

namespace tuco {

struct Circle
{
    double radius;
    Vector3d center;
    Circle(double _radius, Vector3d _center) :
        radius(_radius), center(_center)
    {

    }
    double getRadius()
    {
        return radius;
    }
    bool isInternalPoint(Vector3d _r)
    {
        return (_r - center).norm() < radius;
    }
    Vector3d getCenter()
    {
        return center;
    }
};


struct Polygon
{
    int number;
    double a, b, c; //! it's sides of the triangle
    double area;
    //double incircle;
    Vector3d normal;
    Point barycenter;
    //Point incenter;
    Circle* incircle;
    Circle* circumcircle;
    std::map<std::string, double> sides;
    std::map<std::string, Point*> points;
    Polygon(int _number);
    Polygon(int _number, std::vector<Point*> _points, Vector3d _normal);
    ~Polygon();
    void setSides();
    void setCircles();
    void setBarycenter();
    void setArea();
    bool isNearestPoint(Vector3d _r);
    Vector3d getPointPosition(std::string _name);
    Point getBarycenter();
    /*
    Point getIntercenter()
    {
        return incenter;
    }
    */
    friend std::ostream& operator << (std::ostream& _flux, const Polygon* _polygon)
    {
      std::ios::fmtflags mode = _flux.flags();
      _flux.setf(std::ios::fixed,std::ios::floatfield);
      auto prec = _flux.precision(3);

      _flux
        << "Polygon:  " << _polygon->number << "\n"
        << _polygon->area
        << "_____________________________________________ " << "\n";

      _flux.precision(prec);
      _flux.setf(mode,std::ios::floatfield);
      return _flux;
    }
private:
    double p_;
};

}

#endif // POLYGON_H
