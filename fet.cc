
#include "fet.h"
#include "constants.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace std;

// ************************************ Functions Visible to the User

fet::fet():type(NFET),width(110*pow(10,-9)),length(22*pow(10,-9)),Na(1.45*pow(10,17)),tox(2*pow(10,-9)),MuN(1000)
{
}

fet::fet(int type):type(type),width(110*pow(10,-9)),length(22*pow(10,-9)),Na(1.45*pow(10,17)),tox(2*pow(10,-9)),MuN(1000)
{
}

fet::fet(int type=NFET, float width=110*pow(10,-9), float length=22*pow(10,-9), float Na=1.45*pow(10,17), float tox=2*pow(10,-9), float MuN=1000)
{
   this->type = type;
   this->width = width;
   this->length = length;
   this->Na = Na;
   this->tox = tox;
   this->MuN = MuN;
}

void fet::set_channel_doping(float Na)
{
   this->Na = Na;
   cout << "channel doping set to " << this->Na << endl;\
}

void fet::set_tox_nm(float tox_nm)
{
   try
   {
      if (tox_nm <= 0) throw invalid_argument("Oxide thickness must be greater than 0.\n");
      this->tox = tox_nm*pow(10,-9);
      cout << "tox set to " << this->tox << endl;
   }
   catch (invalid_argument & errObj)
   {
      cout << errObj.what();
   }
}

void fet::set_width_nm(float w_nm)
{
   try
   {
      if (w_nm <= 0) throw invalid_argument("Width must be greater than 0.\n");
      this->width = w_nm*pow(10,-9);
      cout << "width set to " << this->width << endl;
   }
   catch (invalid_argument & errObj)
   {
      cout << errObj.what();
   }
}

void fet::set_length_nm(float len_nm)
{
   try
   {
      if (len_nm <= 0) throw invalid_argument("Length must be greater than 0.\n");
      this->length = len_nm*pow(10,-9);
      cout << "length set to " << this->length << endl;
   }
   catch (invalid_argument & errObj)
   {
      cout << errObj.what();
   }
}

void fet::set_gate_voltage(float v)
{
   this->Vgs = v;
}

void fet::set_drain_voltage(float v)
{
   this->Vds = v;
}

void fet::set_mobility(float MuN)
{
   this->MuN = MuN;
}

float fet::get_width()
{
   return this->width;
}

float fet::get_length()
{
   return this->length;
}

float fet::get_e_mobility()
{
   return this->MuN;
}

float fet::get_drainage_current()
{
   switch(this->get_operating_region())
   {
      case 1:
         // subthreshold
         return 0;
         break;
      case 2:
         // linear
            return this->MuN*this->get_Cox()*(this->width/this->length)*((Vgs - this->get_Vth())*Vds - 0.5*pow(Vds,2));
            break;
      case 3:
         // saturation
         return 0.5*this->MuN*this->get_Cox()*(this->width/this->length)*pow((Vgs - this->get_Vth()),2);
         break;
      default:
         // operating region not defined
         return 0;
         break;
   }
}

float fet::get_psi_beta()
{
   return (kT_OVER_q * log(float(this->Na)/float(ni)));
}

float fet::get_Cox()
{
   return Eox/(this->tox*100);
}

float fet::get_Vth()
{
   return (2*this->get_psi_beta())+(sqrt(4*Esi*q*this->Na*(this->get_psi_beta()))/this->get_Cox());
}

int fet::get_operating_region()
{
   if (this->Vgs < this->get_Vth())
   {
      return SUBTHRESHOLD;
   } 
   else if (this->Vds < (this->Vgs - this->get_Vth()))
   {
      return LINEAR;
   } 
   else
   {
      return SATURATION;
   }
}

void fet::print_operating_region()
{
      switch(this->get_operating_region())
   {
      case 1:
         cout << "The operating region is subthreshold." << endl;
         break;
      case 2:
         cout << "The operating region is linear." << endl;
         break;
      case 3:
         cout << "The operating region is saturation." << endl;
         break;
      default:
         cout << "The operating region is undefined." << endl;
         break;
   }
   return;
}