#ifndef BOX_H
#define BOX_H

#include "shape.h"

namespace tuco {

struct Box : Shape
{
    double length;
    double width;
    double high;
    Box(double _length, double _width, double _high);
    ~Box();
    void setPolygonMesh();
    std::ostream& getStreamInfo(std::ostream& os) const
    {
      long oldprc = os.precision(16);
      os << "-----------------------------------------------------------\n"
         << "    *** Dump for solid - " << getName() << " ***\n"
         << "    ===================================================\n"
         << "Solid type: Box\n"
         << "Parameters: \n"
         << "   half length X: " << length << "\n"
         << "   half length Y: " << width << "\n"
         << "   half length Z: " << high << "\n"
         << "-----------------------------------------------------------\n";
      os.precision(oldprc);
      return os;
    }
};

}

#endif // BOX_H
