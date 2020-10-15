#ifndef DIPOLEMODEL_H
#define DIPOLEMODEL_H

#include "colloid.h"
#include "medium.h"

namespace tuco {

class DipoleModel
{
protected:
    Matrix3d T;
    Environment* environment;
public:
    DipoleModel();
    virtual ~DipoleModel();
    void setMedium(Environment* environment);
    virtual Matrix3d getBlockMatrix(MacroParticle*, MacroParticle*) = 0;
};


class MutualDipoleModel : public DipoleModel
{
    double kappa;
public:
    MutualDipoleModel();
    inline Matrix3d getBlockMatrix(MacroParticle* _particle1, MacroParticle* _particle2);
};

/*
class MutualDipolarModel : public DipoleModel
{
    double kappa;
public:
    MutualDipolarModel()
    {

    }
    Matrix3d getBlockMatrix(Particle* _particle1, Particle* _particle2)
    {
        kappa =  3.0 / (4.0 * ph::pi()) * (*_particle1->object->volume) * (_particle1->object->material->epsilon / medium->getMaterial()->epsilon - 1) / (_particle1->object->material->epsilon / medium->getMaterial()->epsilon + 2);
        if (_particle1 != _particle2) {
            return -medium->getCreenCore()->getDipoleOperator(_particle1->state->r, _particle2->state->r);
        }
        else
        {
            return Matrix3d::Identity(3, 3) / kappa;
        }
    }
};
*/

}


#endif // DIPOLEMODEL_H
