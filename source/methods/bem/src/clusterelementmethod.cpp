#include "clusterelementmethod.h"

namespace tuco {

ClusterElementMethod::ClusterElementMethod(TunableCluster* _cluster, IntegralEquation* _equation) :
    BoundaryElementMethod(_equation, _cluster->getEnvironment()), cluster(_cluster)
{
    sizeMatrix = 0;
    coef1 = shellEquation->getEquationsSize();
    for (auto& iParticle : *cluster->getMacroParticleMap())
    {
        sizeMatrix += shellEquation->getEquationsSize() * iParticle.second->getElementCount();
        sizeMatrix += iParticle.second->getCoreElementCount();
    }
}
ClusterElementMethod::ClusterElementMethod(std::string _type, TunableCluster* _cluster, IntegralEquation* _equation) :
    BoundaryElementMethod(_equation, _cluster->getEnvironment()), type_(_type), cluster(_cluster)
{
    sizeMatrix = 0;
    coef1 = shellEquation->getEquationsSize();
    for (auto& iParticle : *cluster->getMacroParticleMap())
    {
        sizeMatrix += shellEquation->getEquationsSize() * iParticle.second->getElementCount();
        //sizeMatrix += iParticle.second->getCoreElementCount();
    }
}
ClusterElementMethod::ClusterElementMethod(std::string _type, TunableCluster* _cluster, IntegralEquation* _shellEquation, IntegralEquation* _coreEquation) :
    BoundaryElementMethod(_shellEquation, _coreEquation, _cluster->getEnvironment()), type_(_type), cluster(_cluster)
{
    sizeMatrix = 0;
    coef1 = shellEquation->getEquationsSize();
    coef2 = coreEquation->getEquationsSize();
    for (auto& iParticle : *cluster->getMacroParticleMap())
    {
        sizeMatrix += iParticle.second->getElementCount();
        sizeMatrix += iParticle.second->getCoreElementCount();
    }
}
void ClusterElementMethod::setInteractionsMatrix()
{
    matrix = MatrixXd::Zero(sizeMatrix, sizeMatrix);
    if (type_ == "sphere") {
        matrix1 = MatrixXd::Zero(sizeMatrix, sizeMatrix);
        matrix2 = MatrixXd::Zero(sizeMatrix, sizeMatrix);
    }
    value = VectorXd::Zero(sizeMatrix);
//! Заполняем матрицу:
    p = 0;
    for (auto& iParticle1 : *cluster->getMacroParticleMap())
    {
        std::cout << "Number of particle: " << iParticle1.second->getNumber() << " / shell" << std::endl;
        q = 0;
        for (auto& iParticle2 : *cluster->getMacroParticleMap())
        {
            std::cout << iParticle2.second->getNumber() << " / shell" << std::endl;
            if (type_ != "sphere") {
                shellEquation->setMatrixElement(p, q, matrix, iParticle1.second, iParticle2.second);
            }
            else {
                if (iParticle1.second->getNumber() == iParticle2.second->getNumber()) {
                    shellEquation->setMatrixElement(p, q, matrix1, iParticle1.second, iParticle2.second);
                }
                else {
                    shellEquation->setMatrixElement(p, q, matrix2, iParticle1.second, iParticle2.second);
                }
            }
            q += coef1 * iParticle2.second->getElementCount();
            if (iParticle2.second->existSimpleCore()) {
                q += coef1 * iParticle2.second->getCoreElementCount();
            }
            /*
            if (iParticle2.second->existNanoInclusionCore()) {
                q += iParticle2.second->getCoreElementCount();
            }
            */
        }
        p += coef1 * iParticle1.second->getElementCount();

        if (iParticle1.second->existSimpleCore()) {
            std::cout << "Number of particle: " << iParticle1.second->getNumber() << " / core" << std::endl;
            q = 0;
            for (auto& iParticle2 : *cluster->getMacroParticleMap())
            {
                std::cout << iParticle2.second->getNumber() << " / core" << std::endl;
                if (type_ != "sphere") {
                    coreEquation->setMatrixElement(p, q, matrix, iParticle1.second, iParticle2.second);
                }
                else {
                    if (iParticle1.second->getNumber() == iParticle2.second->getNumber()) {
                        coreEquation->setMatrixElement(p, q, matrix1, iParticle1.second, iParticle2.second);
                    }
                    else {
                        coreEquation->setMatrixElement(p, q, matrix2, iParticle1.second, iParticle2.second);
                    }
                }
                q += coef1 * iParticle2.second->getElementCount();
                if (iParticle2.second->existSimpleCore()) {
                    q += coef1 * iParticle2.second->getCoreElementCount();
                }
            }
            p += coef1 * iParticle1.second->getCoreElementCount();
        }
    }
    if (type_ == "sphere") {
        matrix = matrix1 + matrix2;
    }
    flagMatrix = true;
/*
//**Стабилизируем решение:
    delta = MatrixXd::Zero(sizeMatrix, sizeMatrix);
    p = 0;
    for(auto &&iParticle : *cluster->getMacroParticleMap())
    {
        setStabilizingBlock(p, p, iParticle.second);
        p += coef1 * iParticle.second->getElementCount();
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
/*
    std::string fullAddress1 = "matrix1.txt";
    std::ofstream out1(fullAddress1, std::ios::out | std::ios::binary);
    for (int p = 0; p < sizeMatrix; p++)
    {
        for (int q = 0; q < sizeMatrix; q++)
        {
            out1 << matrix1(p, q) << " ";
        }
        out1 << "\n";
    }
    out1.close();
    std::string fullAddress2 = "matrix2.txt";
    std::ofstream out2(fullAddress2, std::ios::out | std::ios::binary);
    for (int p = 0; p < sizeMatrix; p++)
    {
        for (int q = 0; q < sizeMatrix; q++)
        {
            out2 << matrix2(p, q) << " ";
        }
        out2 << "\n";
    }
    out2.close();
    std::cin. get();
*/
}
void ClusterElementMethod::setSurfaceMultipoles(VectorXd _value)
{
    int iter = 0;
    p = 0;
    if (type_ == "sphere") {
        _value = _value + sigma;
    }
    for (auto& iParticle : *cluster->getMacroParticleMap())
    {
        for (auto &iElement : *iParticle.second->getBoundaryElements())
        {
            if (shellEquation->isDipoleExist()) {
                iElement->setDipoleDensity(_value((iElement->getNumber() - 1) + p));
                iter = 1;
            }
            if (shellEquation->isChargeExist()) {
                iElement->setChargeDensity(_value(iter * iParticle.second->getElementCount() + (iElement->getNumber() - 1) + p));
                iter = 0;
            }
        }
        p += coef1 * iParticle.second->getElementCount();
        if (iParticle.second->existSimpleCore()) {
            for (auto &iElement : *iParticle.second->getCoreBoundaryElements())
            {
                iElement->setChargeDensity(_value((iElement->getNumber() - 1) + p));
            }
            p += iParticle.second->getCoreElementCount();
        }
    }
}
void ClusterElementMethod::setColumnVector(ph::ElectricField* _field)
{
    if (type_ == "sphere") {
        sigma = VectorXd::Zero(sizeMatrix);
    //! (1) Заполняем столбец аналитических решений:
        p = 0;
        for (auto& iParticle : *cluster->getMacroParticleMap())
        {            
            if (iParticle.second->existSimpleCore()) { // (a) For Core-Shell particles:
                beta = pow(iParticle.second->getCoreShape()->getCharacteristicSize() / iParticle.second->getShape()->getCharacteristicSize(), 3);
                shellClausius = ph::getClausiusFactor(iParticle.second->getMaterial()->epsilon / cluster->getEnvironmentMaterial()->epsilon);
                coreClausius = ph::getClausiusFactor(iParticle.second->getCoreMaterial()->epsilon / iParticle.second->getMaterial()->epsilon);
                shellPolariazation = shellClausius * (1.0 + 2.0 * beta * coreClausius)  / (1.0 + 2.0 * beta * shellClausius * coreClausius);
                corePolariazation = coreClausius * (1.0 - shellClausius)  / (1.0 + 2.0 * beta * shellClausius * coreClausius);
                for (auto &iElement : *iParticle.second->getBoundaryElements())
                {
                    sigma((iElement->getNumber() - 1) + p) = 3.0 / (4.0 * M_PI) * shellPolariazation * _field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
                }
                p += coef1 * (iParticle.second->getElementCount());
                for (auto &iElement : *iParticle.second->getCoreBoundaryElements())
                {
                    sigma((iElement->getNumber() - 1) + p) = -3.0 / (4.0 * M_PI) * corePolariazation * _field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
                }
                p += coef1 * (iParticle.second->getCoreElementCount());
            } else {                                   // (b) For Simple particles:
                double clausis = (iParticle.second->getMaterial()->epsilon - cluster->getEnvironmentMaterial()->epsilon)
                        / (iParticle.second->getMaterial()->epsilon + 2.0 * cluster->getEnvironmentMaterial()->epsilon);
                for (auto &iElement : *iParticle.second->getBoundaryElements())
                {
                    sigma((iElement->getNumber() - 1) + p) = 3.0 / (4.0 * M_PI) * clausis * _field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
                }
                p += coef1 * (iParticle.second->getElementCount());
            }
        }
    //! (2) Заполянем столбец для численного решения6
        value = -matrix2 * sigma;

    }
    else {
        p = 0;
        for (auto& iParticle : *cluster->getMacroParticleMap())
        {            
            shellEquation->setColumnVector(p, value, iParticle.second, _field);
            p += coef1 * (iParticle.second->getElementCount());
            if (iParticle.second->existSimpleCore()) {
                coreEquation->setColumnVector(p, value, iParticle.second, _field);
                p += coef1 * (iParticle.second->getCoreElementCount());
            }
        }
    }
}

}
