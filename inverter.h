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
      nfet * n_fet;
      pfet * p_fet;
      float Vdd;
      float get_Rn();
      float get_Rp();
      float get_Cl();
};

#endif