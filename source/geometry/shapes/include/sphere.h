#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

namespace tuco {

struct Sphere : Shape
{
    Sphere(double _radius)
    {
        name = "sphere";
        radius = _radius;
        volume = 4.0 / 3.0 * ph::pi() * pow(radius, 3);
        setPolygonMesh();
    }
    Sphere(std::string _name, double _radius)
    {
        name = _name;
        radius = _radius;
        volume = 4.0 / 3.0 * ph::pi() * pow(radius, 3);
        setPolygonMesh();
    }
    ~Sphere()
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
};

}

#endif // SPHERE_H
