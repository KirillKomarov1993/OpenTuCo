#include "dynamicsmatrix.h"

namespace phonon {

DynamicsMatrix::DynamicsMatrix(atom::AtomCrystal* _crystal) :
    crystal(_crystal)
{
    tensor = new ForceTensor(crystal);
    size = static_cast<int>(crystal->getDimension() * crystal->getStructure()->getLatticeCount());

}
void DynamicsMatrix::setMatrix(cs::WaveVector* _wave)
{
    //size = 3;
    D = MatrixXcd::Zero(size, size);
    wave = _wave;
    for (auto iBlock : tensor->blocks)
    {
        D += *iBlock.getMatrix() * exp(-ph::i() * _wave->getValue().dot(iBlock.getPosition()));
    }
}
std::vector<Phonon> DynamicsMatrix::getEigenValues()
{
    VectorXd values;
    std::vector<Phonon> phonons;
    Eigen::ComplexEigenSolver<Eigen::MatrixXcd> es(D);
    values = es.eigenvalues().real();
    for (int i = 0; i < values.size(); i++)
    {
        phonons.push_back(Phonon(*wave, sqrt(values[i])));
    }
    return phonons;
}

}
