#include "inverter.h"
#include <cmath>
#include <iostream>

using namespace std;

inverter::inverter():Vdd(2.5)
{
   this->nfet = new fet(NFET);
   this->pfet = new fet(PFET);
}

void inverter::set_Vdd(float Vdd)
{
   this->Vdd = Vdd;
}

fet * inverter::get_nfet()
{
   return this->nfet;
}

fet * inverter::get_pfet()
{
   return this->pfet;
}

float inverter::get_tpHL()
{
   return 0.69*this->get_Rn()*this->get_Cl();
}

float inverter::get_tpLH()
{
   return 0.69*this->get_Rp()*this->get_Cl();
}

float inverter::get_Vdd()
{
   return this->Vdd;
}

float inverter::get_Cl()
{
   return nfet->get_Cox()*nfet->get_width()*nfet->get_length() + pfet->get_Cox()*pfet->get_width()*pfet->get_length();
}

float inverter::get_Rn()
{
   return 1/(float(nfet->get_e_mobility()*nfet->get_Cox()*(nfet->get_width()/nfet->get_length()))*float(Vdd - nfet->get_Vth()));
}

float inverter::get_Rp()
{
   return 1/(float(pfet->get_e_mobility()*pfet->get_Cox()*(pfet->get_width()/pfet->get_length()))*float(Vdd - abs(pfet->get_Vth())));
}
