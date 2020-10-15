#include "tunablesystem.h"

namespace tuco {

TunableSystem::TunableSystem()
{
    numParticles = 0;
}
TunableSystem::TunableSystem(Environment* environment) :
    environment(environment)
{
    numParticles = 0;
}
TunableSystem::~TunableSystem()
{

}
void TunableSystem::setMacroParticle(MacroParticle* macroParticle)
{
    macroParticles[macroParticle->getNumber()] = macroParticle;
    numParticles++;
}
void TunableSystem::clear()
{
    macroParticles.clear();
    numParticles++;
}
unsigned short TunableSystem::getParticleCount()
{
    return numParticles;
}
MacroParticle* TunableSystem::getMacroParticle(unsigned long number)
{
    return macroParticles[number];
}
Environment* TunableSystem::getEnvironment()
{
    return environment;
}
Material* TunableSystem::getEnvironmentMaterial()
{
    return environment->getMaterial();
}

}
