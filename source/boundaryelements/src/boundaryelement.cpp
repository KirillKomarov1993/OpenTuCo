#include "boundaryelement.h"

namespace tuco {

BoundaryElement::BoundaryElement()
{

}
BoundaryElement::BoundaryElement(Polygon* _polygon, State* _state)
{
    polygon_.reset(_polygon);
    state_ = _state;
}
BoundaryElement::~BoundaryElement()
{

}
//**Базовые методы:
int BoundaryElement::getNumber()
{
    return polygon_->number;
}
double BoundaryElement::getArea()
{
    return polygon_->area;
}
bool BoundaryElement::isNearestPosition(Vector3d _r)
{
    return (_r - getBarycenter()).norm() < 3.0 * getPolygon()->incircle->getRadius();
}
bool BoundaryElement::isNearestElement(BoundaryElement* _element)
{
    return (getBarycenter() - _element->getBarycenter()).norm() < 3.0 * getPolygon()->incircle->getRadius();
}
Vector3d BoundaryElement::getPointPosition(std::string _name)
{
   return (state_->getPosition() + polygon_->getPointPosition(_name));
}
Vector3d BoundaryElement::getNormal()
{
    return state_->getRotateMatrix() * polygon_->normal;
}
Vector3d BoundaryElement::getBarycenter()
{
    return state_->getRotateMatrix() * (state_->getPosition() + polygon_->barycenter.r);
}
Polygon* BoundaryElement::getPolygon()
{
    return this->polygon_.get();
}

}
