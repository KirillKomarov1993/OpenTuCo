#include "clusterenergymethod.h"

namespace tuco {

ClusterEnergyMethod::ClusterEnergyMethod(TunableCluster* _cluster, Integration* _integralSQ, Integration* _integralMC) :
    EnergyElementMethod(new SurfaceEnergyEquation(_integralSQ, _integralMC), _cluster->getEnvironment()), cluster(_cluster)
{    
    sizeMatrix = 0;
    coef = equation->getEquationsSize();
    for (auto& iParticle : *cluster->getMacroParticleMap())
    {
        sizeMatrix += equation->getEquationsSize() * iParticle.second->getElementCount();
    }
    nullDensityMatrix = new DensityMatrix(static_cast<unsigned short>(sizeMatrix));
    dashDensityMatrix = new DensityMatrix(static_cast<unsigned short>(sizeMatrix));
    greenKernel = new ph::CoulombKernal;
    computerDensityMatrix(&EnergyElementMethod::setNullDensityBlock);
    equation->setDensityMatrix(nullDensityMatrix);
}
void ClusterEnergyMethod::setInteractionsMatrix()
{
    matrix = MatrixXd::Zero(sizeMatrix, sizeMatrix);
    value = VectorXd::Zero(sizeMatrix);

//! Заполняем матрицу:
    p_ = 0;
    for (auto& iParticle1 : *cluster->getMacroParticleMap())
    {
        std::cout << "Number of particle: " << iParticle1.second->getNumber() << std::endl;
        q_ = 0;
        for (auto& iParticle2 : *cluster->getMacroParticleMap())
        {
            std::cout << iParticle2.second->getNumber() << std::endl;
            equation->setMatrixElement(p_, q_, matrix, iParticle1.second, iParticle2.second);
            q_ += coef * iParticle2.second->getElementCount();
        }
        p_ += coef * iParticle1.second->getElementCount();
    }
    flagMatrix = true;

    std::cout << "___________________________________________" << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "|  The matrix was compiled successfully!  |" << std::endl;
    std::cout << "|  Matrix size: " << sizeMatrix << " x " <<  sizeMatrix << std::endl;
    std::cout << "|                                         |" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
/*
    std::string fullAddress = "matrix2.txt";
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
    for (int p = 0; p < sizeMatrix; p++)
    {
        for (int q = 0; q < sizeMatrix; q++)
        {
            out << matrix(p, q) << " ";
        }
        out << "\n";
    }
    out.close();
*/
    //std::cin.get();

}
ph::Energy ClusterEnergyMethod::setEnegyBlock(unsigned short p, unsigned short q, VectorXd& _value, MacroParticle* _particle1, MacroParticle* _particle2)
{
    energy_ = ph::Energy(0.0);
    for (auto &iElement1: *_particle1->getBoundaryElements())
    {
        p_ =  static_cast<unsigned short>(iElement1->getNumber() - 1) + p;
        for (auto &iElement2: *_particle2->getBoundaryElements())
        {
            q_ = static_cast<unsigned short>(iElement2->getNumber() - 1) + q;
            //if (iElement1 != iElement2) {
            //if (iElement1->getBarycenter() != iElement2->getBarycenter()) {
                energy_.addValue(0.5 * (2.0 + (_value(p_) * _value(q_)) ) *
                                  iElement1->getArea() * iElement2->getArea() * greenKernel->getFunction(iElement1->getBarycenter(), iElement2->getBarycenter()) * nullDensityMatrix->getElement(p_, q_));
            //}
        }
    }
    return energy_;
}
void ClusterEnergyMethod::setElementEnergis()
{
    unsigned short p, q;


    p = 0;
    for (auto& iParticle1 : *cluster->getMacroParticleMap())
    {
        energy_ = ph::Energy(0.0);
        q = 0;
        for (auto& iParticle2 : *cluster->getMacroParticleMap())
        {
            //if (iParticle1 != iParticle2) {
                for (auto &iElement1: *iParticle1.second->getBoundaryElements())
                {
                    p_ =  static_cast<unsigned short>(iElement1->getNumber() - 1) + p;
                    for (auto &iElement2: *iParticle2.second->getBoundaryElements())
                    {
                        q_ = static_cast<unsigned short>(iElement2->getNumber() - 1) + q;
                        if (iElement1 != iElement2) {
                        //if (iElement1->getBarycenter() != iElement2->getBarycenter()) {
                            energy_.addValue(0.5 * (unknowns(p_) * unknowns(q_) - 0) *
                                              iElement1->getArea() * iElement2->getArea() * greenKernel->getFunction(iElement1->getBarycenter(), iElement2->getBarycenter()) * nullDensityMatrix->getElement(p_, q_));
                        }
                    }
                }
            //}
            q += coef * iParticle2.second->getElementCount();
        }
        p += coef * iParticle1.second->getElementCount();
        iParticle1.second->getHamiltanian()->setPotentialEnergy("tunable", new MadelungEnergy(energy_));
    }
}
void ClusterEnergyMethod::setColumnVector(ph::ElectricField* _field)
{
    p_ = 0;
    for (auto& iParticle : *cluster->getMacroParticleMap())
    {
        equation->setColumnVector(p_, value, iParticle.second, _field);
        p_ += coef * iParticle.second->getElementCount();
    }
}

}
