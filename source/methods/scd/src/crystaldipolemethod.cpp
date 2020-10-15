#include "crystaldipolemethod.h"

namespace tuco {

CrystalDipoleMethod::CrystalDipoleMethod(TunableCrystal* crystal, DipoleModel* method) :
    SelfConsistentMethod(method), crystal(crystal)
{
    space = crystal->getEnvironment()->getSpace();
    model->setMedium(crystal->getEnvironment());
    sizeMatrix = space->getDimenision() * crystal->getMainUnitCell()->getParticleCount();
}

void CrystalDipoleMethod::setDipoleMoment(VectorXd _p)
{
    Vector3d p_(space->dim);    
    for (auto &iNode : *crystal->getMainUnitCell()->getNodes())
    {
        for (int alpha = 0; alpha < static_cast<int>(space->getDimenision()); alpha++)
        {
            p_(alpha) = _p(alpha + static_cast<int>((iNode->getNumber() - 1) * space->getDimenision()));
        }
        crystal->getMacroParticle(iNode)->setDipole(new ph::Dipole(1, p_));
    }
}

void CrystalDipoleMethod::setInteractionsMatrix()
{
    matrix = MatrixXd::Zero(static_cast<long>(sizeMatrix), static_cast<long>(sizeMatrix));
    for (auto &iNode1 : *crystal->getMainUnitCell()->getNodes())
    {
        //std::cout << "      Number of main particle 1: " << iNode1->getNumber() << std::endl;
        for (auto &iNode2 : *crystal->getMainUnitCell()->getNodes())
        {
            //std::cout << "      Number of main particle 2: " << iNode2->getNumber() << std::endl;
            setBlock(crystal->getMacroParticle(iNode1), crystal->getMacroParticle(iNode2));
        }
        for (auto &iUnitCell : crystal->getUnitCells())
        {
            //std::cout << "   Number of cell: " << iUnitCell->getNumber() << std::endl;
            for (auto &iVirtualNode : *iUnitCell->getNodes())
            {
                //std::cout << "      Number of particle: " << iVirtualNode->getNumber() << std::endl;
                setBlock(crystal->getMacroParticle(iNode1), crystal->getMacroParticle(iVirtualNode));
            }
        }
    }
    flagMatrix = true;
    /*
    std::cout << "___________________________________________" << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "|  The matrix was compiled successfully!  |" << std::endl;
    std::cout << "|  Matrix size: " << sizeMatrix << " x "<<  sizeMatrix << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    */
}

VectorXd CrystalDipoleMethod::getColumnVector(ph::ElectricStrength electricStrength)
{
    std::cin.get();
    VectorXd vStrengthes(sizeMatrix);
    for (auto &iParticle  : *crystal->getMainUnitCell()->getNodes())
    {
        for (int alpha = 0; alpha < static_cast<int>(space->getDimenision()); alpha++)
        {
            vStrengthes(alpha + static_cast<int>((iParticle->getNumber() - 1) * space->getDimenision())) = electricStrength.getVector()(alpha);
        }
    }
    return vStrengthes;
}
VectorXd CrystalDipoleMethod::getColumnVector(ph::ElectricField* electricField)
{
    VectorXd vStrengthes(sizeMatrix);
    for (auto &iParticle  : *crystal->getMainUnitCell()->getNodes())
    {
        for (int alpha = 0; alpha < static_cast<int>(space->getDimenision()); alpha++)
        {
            vStrengthes(alpha + static_cast<int>((iParticle->getNumber() - 1) * space->getDimenision())) = electricField->getElectricStrength(iParticle->getPosition()).getVector()(alpha);
        }
    }    
    return vStrengthes;
}

}
