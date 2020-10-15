#ifndef REACTIONFIELDMETHOD_H
#define REACTIONFIELDMETHOD_H


#include "tucomethod.h"
#include "tunablecluster.h"
#include "curve.h"
#include "rotatingelectricfield.h"

namespace tuco {

class ReactionFieldMethod
{
protected:
    TunableCluster* tunableCluster;
    TuCoMethod* tuco;
    std::vector<ph::ElectricPotential*> potentials;
public:
    ReactionFieldMethod(TunableCluster* _tunableCluster, TuCoMethod* _tuco);
    virtual ~ReactionFieldMethod()
    {

    }
    void record(std::string _address, std::string _name)
    {
        std::string fullAddress = _address + _name + ".rf"; // ReactionField
        std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
        for (auto& iPotential : potentials)
        {
            out << iPotential->r(0)
                << "  "
                << iPotential->r(1)
                << "  "
                << iPotential->r(2)
                << "  "
                << iPotential->scalar
                << "\n";
        }
        out.close();
    }
    virtual void computerReactionField(Curve* _curve) = 0;
    virtual void computerPolarizationTensor() = 0;
    virtual void computerMultipoleTensor() = 0;
};



class BEMReactionFieldMethod : public ReactionFieldMethod
{
    ph::HomogeneousRotatingField* field;
public:
    BEMReactionFieldMethod(TunableCluster* _tunableCluster, TuCoMethod* _tuco, ph::HomogeneousRotatingField* _field) :
         ReactionFieldMethod(_tunableCluster, _tuco), field(_field)
    {

    }
    ~BEMReactionFieldMethod()
    {

    }
    void computerPolarizationTensor()
    {

    }
    void computerMultipoleTensor()
    {
        tuco->setInteractionsMatrix();
        tuco->computer(field);
        std::cout << "p = " << *tunableCluster->getMacroParticle(1)->getDipole()->getValue() << std::endl;
        std::cout << std::endl;
        std::cout << "D = " << *tunableCluster->getMacroParticle(1)->getQuadrupole()->getValue() << std::endl;
    }
    void computerReactionField(Curve* _curve)
    {
        tuco->setInteractionsMatrix();
        tuco->computer(field);
        tunableCluster->record("");
        //std::cout << tunableCluster->getMacroParticle(1)->getSelfEnergy().getValue() << std::endl;
        //std::cin.get();
        for (auto&& iPoint : *_curve->getPontList()->getPoints())
        {
            potentials.push_back(new ph::ElectricPotential(iPoint.r));
            for (auto iParticle : *tunableCluster->getMacroParticleMap())
            {
                 potentials.back()->scalar += iParticle.second->getElectricPotential(iPoint.r).scalar;
            }
        }
    }
};

}

#endif // REACTIONFIELDMETHOD_H
