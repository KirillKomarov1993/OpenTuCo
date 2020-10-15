#ifndef MESH_H
#define MESH_H

#include <fstream>

#include "mathlist.h"
#include "polygon.h"
#include "pointlist.h"

namespace tuco {

struct Mesh
{
    int numPoints;
    int numPolygones;
    std::string name;
    std::string type;
    PointList* points;
    std::vector<Polygon> polygones;
    Mesh();
    Mesh(std::string _name);
    Mesh(std::string _name, std::string _type);
    double getArea();
    void loadPoints(std::string _address, std::string _name);
    void loadPolygones(std::string _address, std::string _name);
    PointList* getCenters();
};

}

#endif // MESH_H
