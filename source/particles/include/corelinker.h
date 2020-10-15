 #ifndef CORELINKER_H
#define CORELINKER_H

#include "dipole.h"
#include "object.h"
#include "physicalmesh.h"

namespace tuco {

class PhysicalModel;



struct NanoInclusion
{
    NanoInclusion(unsigned long _number, Vector3d _r) :
        number_(_number), r_(_r)
    {

    }
    unsigned long getNumber()
    {
        return number_;
    }
    Vector3d getPosition()
    {
        return r_;
    }
private:
    unsigned long number_;
    Vector3d r_;
    std::shared_ptr<ph::Dipole> dipole_;
};


struct Core
{
    Core()
    {

    }
};

struct NanoInclusionCore : Core
{
    NanoInclusionCore(Object* _object, double _concentration) :
        concentration_(_concentration), object_(_object)
    {
        numInclusion_ = (unsigned long)(concentration_ * object_->getVolume());
    }
    double getRandomNumber(double _max, double _min)
    {
        return _min + double(rand()) / RAND_MAX * (_max - _min);
    }
    void setNanoInclusion()
    {
        double r, phi, theta;
        unsigned long nInclusion = 1;
        while(nInclusion <= numInclusion_)
        {
            r = pow(getRandomNumber(0.0, 1.0), 1.0 / 3.0) * object_->getShape()->getCharacteristicSize();
            phi = 2.0 * M_PI * (getRandomNumber(0.0, 1.0));
            theta = M_PI * getRandomNumber(0.0, 1.0);
            nanoinclusions.push_back(new NanoInclusion(nInclusion, Vector3d(r * sin(theta) * cos(phi), r * sin(theta) * sin(phi), r * cos(theta))));
            nInclusion++;
        }
    }
    void record(std::string _address, std::string _name)
    {
        std::string fullAddress = _address + _name + ".txt"; // .CrystallographicInformationFile
        std::cout << fullAddress << std::endl;
        std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
        for (auto&  iNanoInclusion : nanoinclusions)
        {
            out << iNanoInclusion->getNumber() << " " << iNanoInclusion->getPosition()(0) << " " << iNanoInclusion->getPosition()(1) << " " << iNanoInclusion->getPosition()(2) << "\n";
        }
    }
    std::vector<NanoInclusion*>* getNanoInclusions()
    {
        return &nanoinclusions;
    }
private:
    unsigned long numInclusion_;
    double concentration_;
    std::shared_ptr<Object> object_;
    std::vector<NanoInclusion*> nanoinclusions;
};


struct CoreLinker
{
    CoreLinker()
    {

    }
    //! Для обычного ядра:
    CoreLinker(Object* _object, PhysicalMesh* _physicalmesh, ph::GreenKernel* _greenkernel) :
        object_(_object), physicalmesh_(_physicalmesh), greenkernel_(_greenkernel)
    {
        simplyCoreFlag_ = true;
    }
    //! Для ядра с нано-включениями:
    CoreLinker(NanoInclusionCore* _nanoinclusioncore, PhysicalMesh* _physicalmesh, ph::GreenKernel* _greenkernel) :
        nanoinclusioncore_(_nanoinclusioncore), physicalmesh_(_physicalmesh), greenkernel_(_greenkernel)
    {
        nanoinclusionCoreFlag_ = true;
    }
//! Функции для обычного ядра:
    bool isSimplyCore()
    {
        return simplyCoreFlag_;
    }
    void setObject(Object* _object)
    {
        object_.reset(_object);
    }
    Object* getObject()
    {
        return object_.get();
    }
    PhysicalMesh* getPhysicalMesh()
    {
        return physicalmesh_.get();
    }
    ph::GreenKernel* getGreenKernel()
    {
        return greenkernel_.get();
    }
//! Функции для ядра с нано-включениями:
    bool isNanoInclusionCore()
    {
        return nanoinclusionCoreFlag_;
    }
    NanoInclusionCore* getNanoInclusionCore()
    {
        return nanoinclusioncore_.get();
    }
private:
    bool simplyCoreFlag_ = false;
    bool nanoinclusionCoreFlag_ = false;
    //! Для ядра с нано-включениями:
    std::shared_ptr<NanoInclusionCore> nanoinclusioncore_;
    //! Для обычного ядра:
    std::shared_ptr<Object> object_;
    std::shared_ptr<PhysicalMesh> physicalmesh_;
    std::shared_ptr<ph::GreenKernel> greenkernel_;
};

}


#endif // CORELINKER_H
