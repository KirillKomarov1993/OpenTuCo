#ifndef ELECTRICMESH_H
#define ELECTRICMESH_H

#include "physicalmesh.h"

namespace tuco {

class ElectricMesh : public PhysicalMesh
{
public:
    ElectricMesh();
    ~ElectricMesh() override;
    void record(std::string _address, std::string _name) override
    {         
        std::string fullAddress = _address + _name + ".pmif"; // .CrystallographicInformationFile
        std::cout << fullAddress << std::endl;
        std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
        for (auto&  iElement : boundaryElements)
        {
            out << iElement
                << "\n";
        }
    }
    void setBoundaryElements(Shape* _shape, State* _state) override;
    unsigned short getElementCount() override;
    std::vector<BoundaryElement*>* getBoundaryElements() override;
protected:
    unsigned short numElements;
    std::vector<BoundaryElement*> boundaryElements;
};


}

#endif // ELECTRICMESH_H
