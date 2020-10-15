#ifndef STRENGTH_H
#define STRENGTH_H

#include "mathlist.h"

namespace ph {

struct Strength {
    Vector3d r;
    Vector3d strength;
    Strength();
    Strength(Vector3d _r);
    Strength(Vector3d _strength, Vector3d _r);
    Strength(Strength const& _strength);
    double dot(Vector3d _vector);
    Vector3d getPosition();
    Vector3d getVector();
    Strength& operator=(const Strength& _right);
    Strength& operator+=(const Strength& _right);
    const Strength operator+(const Strength& _right) const;
};

struct StrengthField {
    int numStrengthes;
    std::string name;
    std::vector<Strength> strengthes;
    StrengthField()
    {
        name = "field";
        numStrengthes = 0;
    }
    StrengthField(std::string _name) :
        name(_name)
    {
        numStrengthes = 0;
    }
    Vector3d getMean()
    {
        Eigen::Vector3d mean(0.0, 0.0, 0.0);
        for (auto iStrength : strengthes)
        {
            mean += iStrength.strength;
        }
        return mean / numStrengthes;
    }
    void setElement(Strength _strength);
    void record(std::string);
};

}

#endif // STRENGTH_H
