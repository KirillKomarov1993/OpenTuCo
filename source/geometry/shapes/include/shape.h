#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "mathlist.h"
#include "mesh.h"

namespace tuco {

struct Shape {
    double radius;
    double volume;
    std::string name;
    Mesh* mesh;
    Shape();
    const std::string getName() const;
    virtual ~Shape();
    virtual void setPolygonMesh() = 0;
    virtual double getCharacteristicSize() = 0;
    virtual std::ostream& getStreamInfo(std::ostream& os) const = 0;    
};

}


#endif // SHAPE_H
