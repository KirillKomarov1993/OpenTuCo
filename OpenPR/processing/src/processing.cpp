#include "processing.h"

namespace pr {

Processing::Processing(std::string _namePackage, std::string _fullAddress) :
    namePackage(_namePackage), fullAddress(_fullAddress)
{
    ensemble = new ph::Ensemble();
}


ProcessingLammps::ProcessingLammps(std::string _fullAddress) :
    Processing("lammps", _fullAddress)
{
    nFile = 0;
}
void ProcessingLammps::fineTuning(unsigned long _step, unsigned long _countFile)
{
    this->countFile = _countFile;
    this->stepFile = _step;
}
void ProcessingLammps::setHeader(std::fstream &F)
{
    double x, x_0, y, y_0;
    std::string f;
    F >> f; F >> f;
    F >> f;
    F >> f; F >> f; F >> f; F >> f;
    F >> numParticles;
    F >> f; F >> f; F >> f; F >> f; F >> f; F >> f;
    F >> x_0;
    F >> x;
    F >> y_0;
    F >> y;
    F >> f; F >> f;
    F >> f; F >> f; F >> f; F >> f; F >> f; F >> f;	F >> f;	F >> f;	// ITEM: ATOMS id x y vx vy
    //figure = new Box(Placement(x_0, y_0), x, y);
}
void ProcessingLammps::setEnsemble()
{
    resetPhysState();
    ensemble->setNullPhysState(load());
    for (unsigned long  i = 0; i < getFileCount(); i++)
    {
        std::cout << i << std::endl;
        shiftPhysState();
        ensemble->setPhysState(load());
    }
}

void ProcessingLammps::setFourierEnsemble(cs::Direction* direction)
{
    physstate = new ph::PhysState(nFile);
    resetPhysState();
    ensemble->setNullPhysState(load());
    for (unsigned long  i = 0; i < getFileCount(); i++)
    {
        std::cout << i << std::endl;
        shiftPhysState();
        for (auto& iWave : *direction->getWaveVectors())
        {
            //std::cout << iWave.getNumber() << std::endl;
            physstate->setMaterialPoint(*load(&iWave));
        }
    }
}
ph::PhysState* ProcessingLammps::load()
{
    ph::PhysState* physstate = new ph::PhysState(nFile);
    std::cout << "Loading File, wait..." << std::endl;
    unsigned long s;
    unsigned long nParticle;
    int typeParticle;
    Vector3d r; r << 0.0, 0.0, 0.0;
    Vector3d v; v << 0.0, 0.0, 0.0;
    std::string fileName = fullAddress + "/" +"dump.lammpstrj." + std::to_string(nFile);
    std::fstream F;
    F.open(fileName);
    if (F)
    {
        s = 0;
        setHeader(F);
        physstate->getMaterialPoints()->resize(numParticles);
        while (!F.eof())
        {
            F >> nParticle;
            F >> typeParticle;
            F >> r(0);
            F >> r(1);
            F >> v(0);
            F >> v(1);
            //if (s <= numParticles) {
            physstate->setMaterialPoint(nParticle, ph::MaterialPoint(nParticle, r, v));
            //std::cout << s << std::endl;
            s++;
        }
        F.close();
    }
    //std::cout << ensemble->cAtoms.back().number << std::endl;
    return physstate;
}
ph::MaterialPoint* ProcessingLammps::load(cs::WaveVector* _wave)
{
    //std::cout << "Loading File, wait..." << std::endl;
    unsigned long s;
    unsigned long nParticle;
    int typeParticle;
    uq << 0.0, 0.0, 0.0;
    vq << 0.0, 0.0, 0.0;
    r << 0.0, 0.0, 0.0;
    v << 0.0, 0.0, 0.0;
    std::string fileName = fullAddress + "/" +"dump.lammpstrj." + std::to_string(nFile);
    std::fstream F;
    F.open(fileName);
    if (F)
    {
        s = 0;
        setHeader(F);
        while (!F.eof())
        {
            F >> nParticle;
            F >> typeParticle;
            F >> r(0);
            F >> r(1);
            F >> v(0);
            F >> v(1);
            //if (s <= numParticles) {
            r0 = ensemble->getNullPhysState()->getMaterialPoint(nParticle)->getPosition();
            uq += (r - r0) * exp(_wave->getValue().dot(r0));
            //vq += v * exp(ph::i() * _wave->getValue().dot(ensemble->getNullPhysState()->getMaterialPoint(nParticle)->getPosition()));
            //std::cout << s << std::endl;
            s++;
        }
        F.close();
    }
    return new ph::MaterialPoint(static_cast<unsigned long>(_wave->getNumber()), uq, vq);
}


}
