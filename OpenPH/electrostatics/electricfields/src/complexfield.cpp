#include "externalfiled.h"



void RotatingField::setExternalFields()
{
    int nField = 0;
    if (symmetry->type == "D")
    {
        if (symmetry->atype == "s") {
            omega_ = (symmetry->alpha) / ((double)numFields);
        }
        else if (symmetry->atype == "h"){
            omega_ = (symmetry->alpha) / ((double)numFields - 1);
        }

        for (auto i = 0; i < numFields; i++)
        {
            phi_ = shift_ + i * omega_;
            vector_ << sin(theta_) * cos(phi_), sin(theta_) * sin(phi_), cos(theta_);
            hFields.push_back(HomogeneousField(nField + 1, magnetude * vector_));
            nField++;
        }
    }
    numFields = nField;
}
void RotatingField::record(std::string _address, std::string _name)
{
    std::string fullAdress = _address + _name + ".externalfield";
    std::ofstream out(fullAdress, std::ios::out | std::ios::binary);
    for (auto &iField : hFields) {
        out << iField.strength(0) << " " << iField.strength(1) << " " << iField.strength(2) << "\n";
    }
    out.close();
}
