#include "deformationmethod.h"

namespace cs {

InternalDeformationMethod::InternalDeformationMethod(Crystal* crystal, double _step) :
    DeformationMethod(crystal), step_(_step)
{
    // Стандартные вариации для поиска первой производной:
    variatons_.push_back(Vector3d(+_step / 2.0,    0.0, 0.0));
    variatons_.push_back(Vector3d(-_step / 2.0,    0.0, 0.0));
    variatons_.push_back(Vector3d(   0.0, +_step / 2.0, 0.0));
    variatons_.push_back(Vector3d(   0.0, -_step / 2.0, 0.0));
    /*
    // Стандартные вариации для поиска второй производной:
    variatons_.push_back(Eigen::Vector3d(   0.0, +_step, 0.0));
    variatons_.push_back(Eigen::Vector3d(+_step, +_step, 0.0));
    variatons_.push_back(Eigen::Vector3d(+_step,    0.0, 0.0));
    variatons_.push_back(Eigen::Vector3d(+_step, -_step, 0.0));
    variatons_.push_back(Eigen::Vector3d(   0.0, -_step, 0.0));
    variatons_.push_back(Eigen::Vector3d(-_step, -_step, 0.0));
    variatons_.push_back(Eigen::Vector3d(-_step,    0.0, 0.0));
    variatons_.push_back(Eigen::Vector3d(-_step, +_step, 0.0));
    */
}

InternalDeformationMethod::~InternalDeformationMethod()
{
    delete energy1;
    delete energy2;
    //variatons_.clear();
}
void InternalDeformationMethod::computerElasticModules()
{
    Vector3d module(0.0, 0.0, 0.0);
    for (auto& iNode : *crystal->getMainUnitCell()->getNodes())
    {
    //**Здесь нужно добавить if для выделения побочных частиц в ячейке;
        for (unsigned long i = 0; i < 2; i++) {
            crystal->setVariation(new VirtualShift(iNode->getNumber(), variatons_[2 * i]));
            //iNode->setShift(variatons_[2 * i]);
            computerCellEnergy();
            energy1 = new ph::Energy(crystal->getUnitCellEnergy());
            crystal->setVariation(new VirtualShift(iNode->getNumber(), variatons_[2 * i + 1]));
            //iNode->setShift(variatons_[2 * i + 1]);
            computerCellEnergy();
            energy2 = new ph::Energy(crystal->getUnitCellEnergy());
            module(static_cast<Index>(i)) = (energy1->getValue() - energy2->getValue()) / step_;
        }
        crystal->getElasticModulus()->setModule(iNode->getNumber(), module);
    }
}

}
