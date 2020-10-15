#include "perturbationdipolemethod.h"

Dipole* PerturbationDipoleMethod::getPerturbationDipole(Particle* _particle, HomogeneousField* _field)
{
    chi_ = (*_particle->object->volume) * 3 / (4 * math::pi()) * (_particle->getMaterial()->epsilon / cluster->getMediumMaterial()->epsilon - 1) / (_particle->getMaterial()->epsilon / cluster->getMediumMaterial()->epsilon + 2);
    lambda = chi_;
    p_ = _field->n;
    for (auto&& iParticle2 : cluster->particles)
    {
        if (iParticle2 != _particle) {
            r12 = _particle->getPlacement() - iParticle2->getPlacement();
            r12_norm = r12.norm();
            n12 = r12 / r12_norm;
            r12in3 = (r12_norm * r12_norm * r12_norm);
            p_ += lambda * (3.0 * n12.dot(_field->n) * n12 - _field->n) / r12in3;
            for (auto&& iParticle3 : cluster->particles)
            {
                if (iParticle3 != iParticle2) {
                    r23 = iParticle2->getPlacement() - iParticle3->getPlacement();
                    r23_norm = r23.norm();
                    n23 = r23 / r23_norm;
                    r23in3 = (r23_norm * r23_norm * r23_norm);
                    p_ += lambda * lambda * (9.0 * n12.dot(n23) * n23.dot(_field->n) * n12 - 3.0 * (n12.dot(_field->n) * n12 + n23.dot(_field->n) * n23) + _field->n) / r12in3 / r23in3;
                    for (auto&& iParticle4 : cluster->particles)
                    {
                        if (iParticle4 != iParticle3) {
                            r34 = iParticle3->getPlacement() - iParticle4->getPlacement();
                            r34_norm = r34.norm();
                            n34 = r34 / r34_norm;
                            r34in3 = (r34_norm * r34_norm * r34_norm);
                            p_ += lambda * lambda * lambda * (27.0 * n12.dot(n23) * n23.dot(n34)  * n34.dot(_field->n) * n12
                                    - 9.0 * (n12.dot(n23) * n23.dot(_field->n) * n12 + n23.dot(n34) * n34.dot(_field->n) * n23 + n12.dot(n34) * n34.dot(_field->n) * n12)
                                    + 3.0 * (n12.dot(_field->n) * n12 + n23.dot(_field->n) * n23 + n34.dot(_field->n) * n34) - _field->n) / r12in3 / r23in3 / r34in3;
                        }
                    }
                }
            }
        }

    }
    return new Dipole(1, chi_ * _field->strength.norm() * p_, _particle->getPlacement());
}
void PerturbationDipoleMethod::computer(HomogeneousField* _field)
{
    for (auto&& iParticle : cluster->particles)
    {
        iParticle->setDipoleMoment(getPerturbationDipole(iParticle, _field));
    }
}
