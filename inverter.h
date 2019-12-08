#ifndef INV_H
#define INV_H

#include "fet.h"

using namespace std;

class inverter
{
    public:
      inverter();
      void set_Vdd(float Vdd);
      fet * get_nfet();
      fet * get_pfet();
      float get_tpLH();
      float get_tpHL();
      float get_Vdd();
    private:
      void update_LH_delay();
      void update_HL_delay();
      void update_Rn();
      void update_Rp();
      void update_Cl();
      // Given
      fet * nfet;
      fet * pfet;
      float Vdd;
      // Derived
      float tpLH;
      float tpHL;
      float propogation_delay;
      float leakage_energy;
      float l_h_energy_dissipation;
      float Rn;
      float Rp;
      float Cl;

};

#endif