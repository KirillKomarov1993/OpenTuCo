#include "wienermethod.h"

/*
namespace pr {

WienerMethod::WienerMethod(Processing* _processing) :
    processing(_processing)
{

}
WienerMethod::~WienerMethod()
{

}
void WienerMethod::getFrequencyAxis()
{
    std::vector<double> freq;
    double period = processing->getFileCount() * processing->getTimeStep() * processing->getFileStep();
    double dfreq = 2.0 * ph::pi() / period;
    for (unsigned long i = 0; i < processing->getFileCount(); i++)
    {
        freq.push_back(dfreq * i);
    }
    //recordCollection(freq, "", "freq", "txt");
}
void WienerMethod::computerPhononModes2D(cs::Direction* direction)
{
    double v_pr, v_nr;
    Eigen::Vector3d e_k, e_n;
    std::complex<double> sum_exp;
    mode_L.clear();
    mode_T.clear();
    std::vector<ph::MaterialPoint>* materiapPoints = processing->load()->getMaterialPoints();
    for (auto& iWaveVector : direction->direction)
    {
        e_k = iWaveVector.getValue() / iWaveVector.getValue().norm();
        e_n = ph::getRotationMatrix3D(ph::pi() / 2, 0.0) * iWaveVector.getValue();
        mode_L.push_back(0.0);
        mode_T.push_back(0.0);
        for (auto iState : *materiapPoints)
        {
            v_pr = e_k.dot(iState.getVelocity());
            v_nr = e_n.dot(iState.getVelocity());
            sum_exp = exp(ph::i()*iWaveVector.getValue().dot(iState.getPosition()));
            mode_L.back() += (v_pr * sum_exp);
            mode_T.back() += (v_nr * sum_exp);
        }
    }
}
void WienerMethod::computerPhononModes2D_MPI(cs::Direction* direction)
{
    double v_pr, v_nr;
    Eigen::Vector3d e_k, e_n;
    std::complex<double> sum_exp, sum_L, sum_T;
    mode_L.clear();
    mode_T.clear();
    std::vector<ph::MaterialPoint*>* materiapPoints = processing->load()->getMaterialPoints();
    for (auto& iWaveVector : direction->direction)
    {
        e_k = iWaveVector.getValue() / iWaveVector.getValue().norm();
        e_n = ph::getRotationMatrix3D(ph::pi() / 2, 0.0) * iWaveVector.getValue();
        sum_T = 0;
        sum_L = 0;
        double sum_L_r = 0;
        double sum_L_i = 0;
        double sum_T_r = 0;
        double sum_T_i = 0;

#pragma omp parallel for private(v_pr, v_nr, sum_exp) reduction(+:sum_L_r, sum_T_r, sum_L_i, sum_T_i) num_threads(4)
        for (unsigned long j = 0; j < materiapPoints->size(); j++)
        {
            v_pr = e_k.dot(materiapPoints->at(j).getVelocity());
            v_nr = e_n.dot(materiapPoints->at(j).getVelocity());
            sum_exp = exp(ph::i() * iWaveVector.getValue().dot(materiapPoints->at(j).getPosition()));
            sum_L_r += (v_pr * sum_exp).real();
            sum_L_i += (v_pr * sum_exp).imag();
            sum_T_r += (v_nr * sum_exp).real();
            sum_T_i += (v_nr * sum_exp).imag();
        }
        mode_L.push_back(sum_L_r + ph::i() * sum_L_i);
        mode_T.push_back(sum_T_r + ph::i() * sum_T_i);
    }
}
void WienerMethod::getPowerSpectraDensity(cs::Direction* direction, std::string name)
{
    unsigned long numWaveVectors = direction->getWaveVectors()->size();
    std::vector<std::vector<std::complex<double> > > SP_L(numWaveVectors);
    std::vector<std::vector<std::complex<double> > > SP_T(numWaveVectors);

    std::clock_t clock(void);
    long time_beg = 0;
    for (unsigned long  i = 0; i < processing->getFileCount(); i++)
    {
        time_beg = std::clock() / CLOCKS_PER_SEC;
        std::cout << "Longitudinal mode:	" << i << " / " << processing->getFileCount() <<
                     "    ||  Times: " << time_beg / 60.0 <<  std::endl;
        computerPhononModes2D_MPI(direction);
        processing->shiftPhysState();
        for (unsigned long j = 0; j < numWaveVectors; j++)
        {
            SP_L[j].push_back(mode_L[j]);
            SP_T[j].push_back(mode_T[j]);
        }

    }

    std::string fullAdress_L = name + "_l" + ".psd";
    std::ofstream out_L(fullAdress_L, std::ios::out | std::ios::binary);
    for (unsigned long j = 0; j < numWaveVectors; j++)
    {
        for (unsigned long  i = 0; i < processing->getFileCount() / 2.0; i++)
        {
            out_L << std::abs(ph::applyFFT(SP_L[j])[i]) << "\t";
        }
        out_L << std::endl;
        std::cout << "L/:  FFT: " << j << " / " << numWaveVectors << std::endl;
    }
    out_L.close();

    std::string fullAdress_T = name + "_t" + ".psd";
    std::ofstream out_T(fullAdress_T, std::ios::out | std::ios::binary);
    for (unsigned long  j = 0; j < numWaveVectors; j++)
    {
        for (unsigned long  i = 0; i < processing->getFileCount() / 2.0; i++)
        {
            out_T << std::abs(ph::applyFFT(SP_T[j])[i]) << "\t";
        }
        out_T << std::endl;
        std::cout << "T/:  FFT: " << j << " / " << numWaveVectors << std::endl;
    }
    out_T.close();
}

}

*/
