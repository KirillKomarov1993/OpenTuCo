#include "crystaldeformationmethod.h"

namespace tuco {

TunableDeformationMethod::TunableDeformationMethod(TunableCrystal* colloidCrystal,  ph::HomogeneousRotatingField* field, TuCoMethod* method, double step) :
    cs::InternalDeformationMethod(colloidCrystal, step), method_(method)
{
    this->colloidCrystal_ = colloidCrystal;
    this->field_ = field;
}
TunableDeformationMethod::~TunableDeformationMethod()
{

}
void TunableDeformationMethod::computerCellEnergy()
{
//**Расчет управляемого взаимодействия:
//**Заполнение частиц кристалла диполями:
    colloidCrystal_->reset("energy");
    method_->setInteractionsMatrix();
    while(!field_->isFinish()) {
        method_->computer(field_);
        colloidCrystal_->computerTunableEnergy();
        field_->rotateElectricFeild();
    }
    field_->reset();
    colloidCrystal_->computerMadelungEnergy();
}

}
