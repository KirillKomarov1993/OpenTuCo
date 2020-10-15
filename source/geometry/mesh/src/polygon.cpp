#include "polygon.h"


namespace tuco {

Polygon::Polygon(int _number) :
    number(_number)
{
}
Polygon::Polygon(int _number, std::vector<Point*> _points, Vector3d _normal) :
    number(_number), normal(_normal)
{
    points["A"] = _points[0];
    points["B"] = _points[1];
    points["C"] = _points[2];
    setSides();
    setArea();
    setBarycenter();
    setCircles();
}
Polygon::~Polygon()
{

}
void Polygon::setSides()
{
    a = (points["A"]->r - points["B"]->r).norm();
    b = (points["B"]->r - points["C"]->r).norm();
    c = (points["C"]->r - points["A"]->r).norm();
    sides["a"] = a;
    sides["b"] = b;
    sides["c"] = c;
}
void Polygon::setCircles()
{
    incircle = new Circle(2.0 * area / (sides["a"] + sides["b"] + sides["c"]),
                        (sides["a"] * points["C"]->r + sides["b"] * points["A"]->r + sides["c"] * points["B"]->r) / (sides["a"] + sides["b"] + sides["c"]));
    circumcircle = new Circle((sides["a"] * sides["b"] * sides["c"]) / (4.0 * area),
                        pow(sides["a"], 2) * (points["A"]->r - points["B"]->r).dot(points["A"]->r - points["C"]->r) * points["A"]->r +
                        pow(sides["b"], 2) * (points["B"]->r - points["A"]->r).dot(points["B"]->r - points["C"]->r) * points["A"]->r +
                        pow(sides["c"], 2) * (points["C"]->r - points["A"]->r).dot(points["C"]->r - points["B"]->r) * points["A"]->r);

}
void Polygon::setBarycenter()
{
    barycenter = Point(1, (points["A"]->r + points["B"]->r + points["C"]->r) / 3.0);
}
void Polygon::setArea()
{
    p_ = 0.5 * (sides["a"] + sides["b"] + sides["c"]);
    area = sqrt(p_ * (p_ - sides["a"]) * (p_ - sides["b"]) * (p_ - sides["c"]));
}
bool Polygon::isNearestPoint(Vector3d _r)
{
    return (_r - incircle->getCenter()).norm() < incircle->getRadius();
}
Vector3d Polygon::getPointPosition(std::string _name)
{
    return points[_name]->r;
}
Point Polygon::getBarycenter()
{
    return barycenter;
}

}
