#include "brillouinzone.h"

namespace cs {

BrillouinZone::BrillouinZone(BravaisLattice* _bravais) :
    bravais(_bravais)
{
    reciprocalLattice_ = _bravais->getReciprocalLattice();
    setReciprocalNodes();
}
void BrillouinZone::setReciprocalNodes()
{
    int optimalNearNodes = 4;
    int nNode = 0;
    VectorXd k_;
    for (int i = -optimalNearNodes; i < optimalNearNodes; i++)
    {
        for (int j = -optimalNearNodes; j < optimalNearNodes; j++)
        {
            if (!(i == 0 && j == 0)) {
                k_ = (reciprocalLattice_->getBasis()->getBasisVector(1) * i + reciprocalLattice_->getBasis()->getBasisVector(2) * j);
                if (k_.norm() <= (optimalNearNodes * reciprocalLattice_->getBasis()->getBasisVector(2).norm()) / 2.0) {
                    basicNodes_.push_back(WaveVector(nNode, k_));
                    nNode++;
                }
            }
        }
    }
}
bool BrillouinZone::isBrillouinZone(WaveVector& _wave)
{
    double e = 1e-5;
    bool s = true;
    for (auto iBasicVector : basicNodes_)
    {
        if ((2 * _wave.getValue().dot(iBasicVector.getValue())) + e <= pow(iBasicVector.getValue().norm(), 2))
        {
            s *= true;
        }
        else {
            s *= false;
            continue;
        }
    }
    return s;
}
void BrillouinZone::setBrillouinZone(int _approxNumber)
{
    if (!brillouin.empty()) brillouin.clear();
    approxNumber_ = _approxNumber;
    nWaveVector_ = 0;
    for(int i = -approxNumber_; i < approxNumber_; i++)
    {
        for(int j = -approxNumber_; j < approxNumber_; j++)
        {
            WaveVector* wave = new WaveVector(nWaveVector_, i * reciprocalLattice_->getBasis()->getBasisVector(1) / (approxNumber_ - 1) + j * reciprocalLattice_->getBasis()->getBasisVector(2) / (approxNumber_ - 1));
            if (isBrillouinZone(*wave)) {
                brillouin.push_back(*wave);
                nWaveVector_++;
            }
            delete wave;
        }
    }
    numWaveVectors = nWaveVector_;
}
void BrillouinZone::setDirection(std::string _nameDirection, int _numWaveVectors)
{
    numWaveVectors = _numWaveVectors;
    if (!points_.empty()) points_.clear();
    for (unsigned long i = 0; i <= _nameDirection.size() / 2.0; i++)
    {
        points_.push_back(std::string(1, _nameDirection[2 * i]));
    }

    for (unsigned long nPoint = 1; nPoint < points_.size(); nPoint++)
    {
        Direction* direction = new Direction(points_[nPoint - 1] + "-" +  points_[nPoint]);
        dk_ = (bravais->getCriticalPoint(points_[nPoint]) - bravais->getCriticalPoint(points_[nPoint - 1]))/(numWaveVectors / (points_.size() - 1) - 1);
        for (int i = 0; i < numWaveVectors/(points_.size() - 1); i++)
        {
            direction->setElement(WaveVector(i + numWaveVectors * (nPoint - 1), bravais->getCriticalPoint(points_[nPoint - 1]) + dk_ * i));
        }
        directions.push_back(*direction);
        direction->record("");
        delete direction;
    }
}
void BrillouinZone::record(std::string _address, std::string _name)
{
    std::string fullAddress = _address + _name + ".brillouin";
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);

    for (auto iWaveVector : brillouin)
    {
        out << iWaveVector.getNumber() << "   ";
        for (int i = 0; i < iWaveVector.getValue().size(); i++)
        {
            out << iWaveVector.getValue()(i) << "   ";
        }
        out << "\n";
    }
    out.close();
}

}
