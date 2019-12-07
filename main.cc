
#include "nfet.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
   nfet nf1 = nfet();
   nf1.set_tox_nm(2);
   nf1.set_channel_doping(1.45*pow(10,17));
   cout << "threshold voltage: " << nf1.get_threshold_voltage() << "V\n" << endl;

   nf1.set_width_nm(110);
   nf1.set_length_nm(22);
   nf1.set_mobility(1000);
   nf1.set_gate_voltage(2.0);
   nf1.set_drain_voltage(0.1);
   cout << "Drainage current at linear: " << nf1.get_drainage_current() << "A" << endl;
   nf1.set_gate_voltage(2.5);
   nf1.set_drain_voltage(2.5);
   cout << "Drainage current at saturation: " << nf1.get_drainage_current() << "A\n" << endl;

   
}