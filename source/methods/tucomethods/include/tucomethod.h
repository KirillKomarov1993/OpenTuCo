#ifndef TUCOMETHOD_H
#define TUCOMETHOD_H

#include "homogemiusfield.h"

namespace tuco {

//**Общий интерфейс подо все вычислительные методы (для обобщения методов-приложений):
class TuCoMethod
{
public:
    virtual void computer(ph::ElectricField* _field) = 0;
    virtual void setInteractionsMatrix() = 0;
};

}


#endif // TUCOMETHOD_H
