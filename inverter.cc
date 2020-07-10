#include "inverter.h"
#include <cmath>
#include <iostream>

using namespace std;

inverter::inverter():Vdd(2.5)
{
   this->n_fet = new nfet();
   this->p_fet = new pfet();
}

void inverter::set_Vdd(float Vdd)
{
   this->Vdd = Vdd;
}

fet * inverter::get_nfet()
{
   return this->n_fet;
}

fet * inverter::get_pfet()
{
   return this->p_fet;
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
   return n_fet->get_Cox()*n_fet->get_width()*n_fet->get_length() + p_fet->get_Cox()*p_fet->get_width()*p_fet->get_length();
}

float inverter::get_Rn()
{
   return 1/(float(n_fet->get_e_mobility()*n_fet->get_Cox()*(n_fet->get_width()/n_fet->get_length()))*float(Vdd - n_fet->get_Vth()));
}

float inverter::get_Rp()
{
   return 1/(float(p_fet->get_e_mobility()*p_fet->get_Cox()*(p_fet->get_width()/p_fet->get_length()))*float(Vdd - abs(p_fet->get_Vth())));
}
