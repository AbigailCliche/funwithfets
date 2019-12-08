
#include "fet.h"
#include <iostream>
#include <cmath>
#include "inverter.h"

using namespace std;

int main()
{
   cout << "NFET Analysis HW3" << endl;
   fet nf1 = fet();
   cout << "threshold voltage: " << nf1.get_threshold_voltage() << "V" << endl;
   nf1.set_gate_voltage(2.0);
   nf1.set_drain_voltage(0.1);
   cout << "Drainage current at linear: " << nf1.get_drainage_current() << "A" << endl;
   nf1.set_gate_voltage(2.5);
   nf1.set_drain_voltage(2.5);
   cout << "Drainage current at saturation: " << nf1.get_drainage_current() << "A\n" << endl; 

   cout << "Inverter Analysis HW4" << endl;
   inverter inv = inverter();
   inv.get_nfet()->set_mobility(1000);
   inv.get_pfet()->set_mobility(500);
   inv.get_nfet()->set_width_nm(110);
   inv.get_pfet()->set_width_nm(220);
   inv.get_nfet()->set_new_threshold_voltage(0.5);
   inv.get_pfet()->set_new_threshold_voltage(0.5);
   cout << "tpHL: " << inv.get_tpHL() << "s" << endl;
   cout << "tpLH: " << inv.get_tpLH() << "s\n" << endl;
   cout << "n threshold voltage: " << inv.get_nfet()->get_threshold_voltage() << "V" << endl;
}

