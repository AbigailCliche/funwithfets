#include "inverter.h"
#include <cmath>

using namespace std;

inverter::inverter():Vdd(2.5)
{
   this->nfet = new fet(NFET);
   this->pfet = new fet(PFET);
   update_Rn();
   update_Rp();
   update_Cl();
}

void inverter::set_Vdd(float Vdd)
{
   this->Vdd = Vdd;
   update_Rn();
   update_Rp();
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
   return this->tpHL;
}

float inverter::get_tpLH()
{
   return this->tpLH;
}

float inverter::get_Vdd()
{
   return this->Vdd;
}

void inverter::update_Cl()
{
   this->Cl = nfet->get_cox()*nfet->get_width()*nfet->get_length() + pfet->get_cox()*pfet->get_width()*pfet->get_length();
}

void inverter::update_Rn()
{
   this->Rn = 1/(float(nfet->get_e_mobility()*nfet->get_cox()*(nfet->get_width()/nfet->get_length()))*float(Vdd - nfet->get_threshold_voltage()));
   update_HL_delay();
}

void inverter::update_Rp()
{
   this->Rp = 1/(float(pfet->get_e_mobility()*pfet->get_cox()*(pfet->get_width()/pfet->get_length()))*float(Vdd - abs(pfet->get_threshold_voltage())));
   update_LH_delay();
}

void inverter::update_HL_delay()
{
   this->tpHL = 0.69*Rn*Cl;
}

void inverter::update_LH_delay()
{
   this->tpLH = 0.69*Rp*Cl;
}
