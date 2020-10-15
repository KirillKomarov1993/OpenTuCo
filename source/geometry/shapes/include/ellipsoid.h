#ifndef ELLIPSOID_H
#define ELLIPSOID_H


#include "shape.h"

namespace tuco {

struct Ellipsoid : Shape
{
    Ellipsoid(double _a, double _b, double _c) :
        a_(_a), b_(_b), c_(_c)
    {
        name = "ellipsoid";
        radius = a_ * pow(b_ * c_ / (a_ * a_), 1.0 / 3.0);
        volume = 4.0 / 3.0 * ph::pi() * pow(radius, 3);
        setPolygonMesh();
    }
    Ellipsoid(std::string _name, double _radius)
    {
        name = _name;
        radius = _radius;
        volume = 4.0 / 3.0 * ph::pi() * pow(radius, 3);
        setPolygonMesh();
    }
    ~Ellipsoid()
    {

    }
    void setPolygonMesh()
    {
        mesh = new Mesh(name);
    }
    double getCharacteristicSize()
    {
        return radius;
    }
    double getSizeX()
    {
        return radius;
    }
    double getSizeY()
    {
        return radius;
    }
    double getSizeZ()
    {
        return radius;
    }
    std::ostream& getStreamInfo(std::ostream& os) const
    {
      long oldprc = os.precision(16);
      os << "-----------------------------------------------------------\n"
         << "    *** Dump for solid - " << getName() << " ***\n"
         << "    ===================================================\n"
         << "Solid type: Sphere\n"
         << "Parameters: \n"
         << "   half length X: " << radius << "\n"
         << "-----------------------------------------------------------\n";
      os.precision(oldprc);
      return os;
    }
private:
    double a_;
    double b_;
    double c_;
};

}

#endif // ELLIPSOID_H
