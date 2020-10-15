#ifndef DISPERSIONMODEL_H
#define DISPERSIONMODEL_H

#include <medium.h>

namespace tuco {

// Interface:
struct DispersionModel
{    
    Medium* medium;
    void setMedium(Medium* _medium)
    {
        medium = _medium;
    }
};

// Realization1:
struct DLVOModel : public DispersionModel
{
    DLVOModel()
    {

    }
 private:
    double gamaker;

};

}

#endif // DISPERSIONMODEL_H
