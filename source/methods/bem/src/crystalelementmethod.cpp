#include "crystalelementmethod.h"

namespace tuco {

CrystalElementMethod::CrystalElementMethod(TunableCrystal* _crystal, IntegralEquation* _equation) :
    BoundaryElementMethod(_equation, _crystal->getEnvironment()), crystal(_crystal)
{
    sizeMatrix = 0;
    for (auto& iNode : *crystal->getMainUnitCell()->getNodes())
    {
        sizeMatrix += shellEquation->getEquationsSize() * crystal->getMacroParticle(iNode)->getElementCount();
    }
}
void CrystalElementMethod::setInteractionsMatrix()
{
    matrix = MatrixXd::Zero(sizeMatrix, sizeMatrix);
    value = VectorXd::Zero(sizeMatrix);
//! Заполняем матрицу:
    std::cout << "Interaction Matrix" << std::endl;
    for (auto &iCell : crystal->getUnitCells())
    {
        std::cout << "   Number of cell: " << iCell->getNumber() << std::endl;
        p = 0;
        for (auto &iNode1 : *crystal->getMainUnitCell()->getNodes())
        {
            std::cout << "      Number of particle: " << iNode1->getNumber() << std::endl;
            q = 0;
           // std::cout << crystal->getMacroParticle(iNode1)->getPosition() << std::endl;
            for (auto &iNode2 : *iCell->getNodes())
            {
                shellEquation->setMatrixElement(p, q, matrix, crystal->getMacroParticle(iNode1), crystal->getMacroParticle(iNode2));
                q += coef1 * crystal->getMacroParticle(iNode2)->getElementCount();
            }
            p += coef1 * crystal->getMacroParticle(iNode1)->getElementCount();
        }
        //std::cin.get();
    }
    flagMatrix = true;

//! Стабилизируем решение:
/*
    delta = Matrix::Zero(sizeMatrix_, sizeMatrix_);
    for(auto &iParticle : system->particles)
    {
        setStabilizingBlock(iParticle);
    }
    matrix = matrix * delta;
*/
//!
    std::cout << "___________________________________________" << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "|  The matrix was compiled successfully!  |" << std::endl;
    std::cout << "|  Matrix size: " << sizeMatrix << " x " <<  sizeMatrix << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
}
void CrystalElementMethod::setSurfaceMultipoles(VectorXd _value)
{
    int iter = 0;
    p = 0;
    MacroParticle* macroParticle;
    for (auto &iNode : *crystal->getMainUnitCell()->getNodes())
    {
        macroParticle = crystal->getMacroParticle(iNode);
        for (auto &iElement : *crystal->getMacroParticle(iNode)->getBoundaryElements())
        {
            if (shellEquation->isDipoleExist()) {
                iElement->setDipoleDensity(_value((iElement->getNumber() - 1) + p));
                iter = 1;
            }
            if (shellEquation->isChargeExist()) {
                iElement->setChargeDensity(_value(iter * macroParticle->getElementCount() + (iElement->getNumber() - 1) + p));
                iter = 0;
            }
        }
        p += coef1 * macroParticle->getElementCount();
    }
}
void CrystalElementMethod::setColumnVector(ph::ElectricField* _field)
{
    p = 0;
    MacroParticle* macroParticle;
    for (auto &iNode : *crystal->getMainUnitCell()->getNodes())
    {
        macroParticle = crystal->getMacroParticle(iNode);
        shellEquation->setColumnVector(p, value, macroParticle, _field);
        p += coef1 * macroParticle->getElementCount();
    }
}

}
