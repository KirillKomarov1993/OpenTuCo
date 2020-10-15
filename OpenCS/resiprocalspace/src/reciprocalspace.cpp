#include "reciprocalspace.h"

namespace cs {

/*

ReciprocalLattice::ReciprocalLattice(Basis* _basis) :
    basis_(_basis)
{
    dim_ = basis_->dim;
    setBasicNode();
}
ReciprocalLattice::ReciprocalLattice(BravaisLattice* _lattice)
{
    _lattice->getBasis();
    dim_ = basis_->dim;
    setBasicNode();
}
void ReciprocalLattice::setBasicNode()
{
    int optimalNearNodes = 4;
    int nNode = 0;
    for (int i = -optimalNearNodes; i < optimalNearNodes; i++)
    {
        for (int j = -optimalNearNodes; j < optimalNearNodes; j++)
        {
            if (!(i == 0 && j == 0)) {
                k_ = (basis_->a[0]) * i + (basis_->a[1]) * j;
                if (k_.norm() <= (optimalNearNodes * (basis_->a[0]).norm()) / 2.0) {
                    basicNodes_.push_back(WaveVector(nNode, k_));
                    nNode++;
                }
            }
        }
    }
    numBasicNodes_ = nNode;
}
void ReciprocalLattice::record(std::string _address, std::string _name)
{
    std::string fullAddress = _address + _name + ".rsf"; // ResiprocalSpaceFormat
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);

    for (auto iBasicNode : basicNodes_)
    {
        out << iBasicNode.getNumber() << "   ";
        for (int i = 0; i < iBasicNode.getValue().size(); i++)
        {
            out << iBasicNode.getValue()(i) << "   ";
        }
        out << "\n";
    }
    out.close();
}

*/

}
