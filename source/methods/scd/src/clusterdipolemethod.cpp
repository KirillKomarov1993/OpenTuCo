#include "clusterdipolemethod.h"

namespace tuco {

ClusterDipoleMethod::ClusterDipoleMethod(TunableCluster* _cluster, DipoleModel* _model) :
    SelfConsistentMethod(_model), cluster(_cluster)
{
    space = cluster->getEnvironment()->getSpace();
    model->setMedium(cluster->getEnvironment());
    sizeMatrix = space->dim * cluster->getParticleCount();
    //std::cout << sizeMatrix << std::endl;
    //std::cin.get();
}
void ClusterDipoleMethod::setInteractionsMatrix()
{
    matrix = MatrixXd::Zero(static_cast<Index>(sizeMatrix), static_cast<Index>(sizeMatrix));
    for (auto &iParticle1 : *cluster->getMacroParticleMap())
    {
        std::cout << "Number of particle: " << iParticle1.second->getNumber() << std::endl;
        for (auto &iParticle2 : *cluster->getMacroParticleMap())
        {
            setBlock(iParticle1.second, iParticle2.second);
        }
    }
    flagMatrix = true;
    std::cout << "___________________________________________" << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "|  The matrix was compiled successfully!  |" << std::endl;
    std::cout << "|  Matrix size: " << sizeMatrix << " x "<<  sizeMatrix << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
}

VectorXd ClusterDipoleMethod::getColumnVector(ph::ElectricField* electricField)
{
    VectorXd vStrengthes(sizeMatrix);
    int nElement = 0;
    for (auto &iParticle : *cluster->getMacroParticleMap())
    {
        for (int alpha = 0; alpha < static_cast<int>(space->getDimenision()); alpha++)
        {
            vStrengthes(nElement) = electricField->getElectricStrength(iParticle.second->getPosition()).getVector()(alpha);;
            nElement++;
        }
    }
    return vStrengthes;
}

void ClusterDipoleMethod::setDipoleMoment(VectorXd _p)
{
    Vector3d p_(space->dim);
    for (auto &iParticle : *cluster->getMacroParticleMap())
    {
        for (int alpha = 0; alpha < space->getDimenision(); alpha++)
        {
            p_(alpha) = _p(alpha + (iParticle.second->getNumber() - 1) * space->getDimenision());
        }
        iParticle.second->setDipole(new ph::Dipole(1, p_, iParticle.second->getPosition()));
    }
}

}
