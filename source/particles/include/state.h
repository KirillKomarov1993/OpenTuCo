#ifndef STATE_H
#define STATE_H

#include "mathlist.h"

namespace tuco {

struct State
{    
    State();
    State(int _number, Vector3d _r);
    State(int _number, Vector3d _r, double _theta);
//**Базовые функции и методы:
    void setPosition(Vector3d _r);
    void setVariation(Vector3d _u);
    void resetVariation();
    int getNumber();
    Vector3d getPosition();    
//**
    void setOrientation(Vector3d _r);
    Vector3d getOrientation();
    Matrix3d getRotateMatrix();
private:
    int number;
    double theta_;
    bool vFlag;
    Vector3d r; // position;
    Vector3d u; // variation of the position;
    Vector3d n; // variation of the position;
    Matrix3d R1;
    void setRotateMatrix();
};

}




#endif // STATE_H
