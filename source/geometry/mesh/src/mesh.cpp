#include "mesh.h"
//#include "sys/types.h"
//#include "sys/stat.h"
//#include "dirent.h"

namespace tuco {

Mesh::Mesh()
{
    numPoints = 0;
    numPolygones = 0;
    points = new PointList();
}
Mesh::Mesh(std::string _name) :
    name(_name)
{
    numPoints = 0;
    numPolygones = 0;
    type = "normal";
    points = new PointList();
    loadPoints("geometry/shapes/", name);
    loadPolygones("geometry/shapes/", name);
}
Mesh::Mesh(std::string _name, std::string _type) :
    name(_name), type(_type)
{
    numPoints = 0;
    numPolygones = 0;
    points = new PointList();
    loadPoints("geometry/shapes/", name);
    loadPolygones("geometry/shapes/", name);
}
double Mesh::getArea()
{
    double area = 0.0;
    for (auto iPolygon : polygones)
    {
        area += iPolygon.area;
    }
    return area;
}
void Mesh::loadPoints(std::string _address, std::string _name)
{
/*
    DIR *dir = opendir(".");
    if(dir)
    {
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL)
    {
    puts(ent->d_name);
    }
    }
    else
    {
    fprintf(stderr, "Error opening directory\n");
    }
    std::cout << _name + ".points" << std::endl;
    std::cin.get();
*/

    //if (!points->empty()) points->clear();
    int nPoint = 0;
    int dim = 3;
    Vector3d r(dim);

    std::ifstream F;
    F.open (_address + _name + ".points", std::ios::in | std::ios::binary);
    if (F)
    {
        while (!F.eof())
        {
            nPoint++;
            F >> r(0);
            F >> r(1);
            F >> r(2);
            points->setPoint(Point(nPoint, r));
        }
        F.close();
    }
//! КОСТЫЛЬ! //
    if (!points->points.empty()) {
        points->points.pop_back();
        nPoint--;
    }
    numPoints = nPoint;
}
void Mesh::loadPolygones(std::string _address, std::string _name)
{
    if (!polygones.empty()) polygones.clear();
    int nPolygone_ = 0;
    int number_;
    std::vector<Point*> pPolygone_;
    Eigen::Vector3d n_;
    std::ifstream F;
    F.open(_address + _name + ".polygones", std::ios::in | std::ios::binary);
    if (F)
    {
        while (!F.eof())
        {

            pPolygone_.clear();
            nPolygone_++;
            for (int i = 0; i < 3; i++) {
                F >> number_;
                pPolygone_.push_back(points->getPoint(number_));
            }
            if (type == "normal") {
                for (int i = 0; i < 3; i++) {
                    F >> n_(i);
                }
            }
            else if (type == "linear") {
                F >> number_;
            }
            polygones.push_back(Polygon(nPolygone_, pPolygone_, n_));
        }
        F.close();
    }
    //! КОСТЫЛЬ! //
    if (!polygones.empty()) {
        polygones.pop_back();
        nPolygone_ --;
    }
    numPolygones = nPolygone_;
}
PointList* Mesh::getCenters()
{
    PointList* pointlist = new PointList;
    for (auto &iPolygon : polygones)
    {
        pointlist->setPoint(iPolygon.barycenter);
    }
    return pointlist;
}

}
