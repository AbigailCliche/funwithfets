
#include "nfet.h"
#include "constants.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace std;

// ************************************ Functions Visible to the User

void nfet::set_channel_doping(float Na)
{
   this->Na = Na;
   cout << "channel doping set to " << this->Na << endl;
   update_psi_beta();
   update_threshold_voltage();
}

void nfet::set_tox_nm(float tox_nm)
{
   try
   {
      if (tox_nm <= 0) throw invalid_argument("Oxide thickness must be greater than 0.\n");
      this->tox = tox_nm*pow(10,-9);
      cout << "tox set to " << this->tox << endl;
      update_threshold_voltage();
      update_oxide_capacitance();
   }
   catch (invalid_argument & errObj)
   {
      cout << errObj.what();
   }
}

void nfet::set_width_nm(float w_nm)
{
   try
   {
      if (w_nm <= 0) throw invalid_argument("Width must be greater than 0.\n");
      this->width = w_nm*pow(10,-9);
      cout << "width set to " << this->width << endl;
      update_drainage_current();
   }
   catch (invalid_argument & errObj)
   {
      cout << errObj.what();
   }
}

void nfet::set_length_nm(float len_nm)
{
   try
   {
      if (len_nm <= 0) throw invalid_argument("Length must be greater than 0.\n");
      this->length = len_nm*pow(10,-9);
      cout << "length set to " << this->length << endl;
      update_drainage_current();
   }
   catch (invalid_argument & errObj)
   {
      cout << errObj.what();
   }
}

void nfet::set_gate_voltage(float v)
{
   this->Vgs = v;
   update_operating_region();
}

void nfet::set_drain_voltage(float v)
{
   this->Vds = v;
   update_operating_region();
}

void nfet::set_mobility(float MuN)
{
   this->MuN = MuN;
   update_drainage_current();
}


float nfet::get_drainage_current()
{
   return this->drainage_current;
}

float nfet::get_threshold_voltage()
{
   return this->Vth;
}



// ************************************ Functions Not to be used by the User

void nfet::update_oxide_capacitance()
{
   this->Cox = Eox/(this->tox*100);  
}

void nfet::update_drainage_current()
{
   switch(this->operating_region)
   {
      case 1:
         // subthreshold
         this->drainage_current = 0;
         break;
      case 2:
         // linear
         this->drainage_current = this->MuN*this->Cox*(this->width/this->length)*((Vgs - Vth)*Vds - 0.5*pow(Vds,2));
            break;
      case 3:
         // saturation
         this->drainage_current = 0.5*this->MuN*this->Cox*(this->width/this->length)*pow((Vgs - Vth),2);
         break;
      default:
         // operating region not defined
         this->drainage_current = 0;
         break;
   }
   return;
}

void nfet::update_psi_beta()
{
   this->psi_beta = (kT_OVER_q * log(float(this->Na)/float(ni)));
   cout << "psi_beta updated to " << this->psi_beta << endl;
}

void nfet::update_threshold_voltage()
{
   this->Vth = (2*this->psi_beta)+(sqrt(4*Esi*q*this->Na*(this->psi_beta))/this->Cox);
   cout << "Vth updated to " << this->Vth << endl;
   update_operating_region();
}


// void nfet::update_depletion_width() //tsi
// {
//    this->depletion_width = sqrt(float(2*Esi*2*this->psi_beta)/float(this->Na));
// }

void nfet::update_operating_region()
{
   if (this->Vgs < this->Vth)
   {
      this->operating_region = SUBTHRESHOLD;
      cout << "Operating region updated to SUBTHRESHOLD."<< endl;
   } 
   else if (Vds < (Vgs - Vth))
   {
      this->operating_region = LINEAR;
      cout << "Operating region updated to LINEAR."<< endl;
   } 
   else
   {
      this->operating_region = SATURATION;
      cout << "Operating region updated to SATURATION."<< endl;
   }
   update_drainage_current();
}