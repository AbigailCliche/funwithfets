#ifndef FET_H
#define FET_H

#define SUBTHRESHOLD 1
#define LINEAR 2
#define SATURATION 3

#define PFET 0
#define NFET 1

// TODO 
// consider differences between PMOS and NMOS in slide deck 7
// Finish HW 3 problem 3

// Pfet Vth < 0
// Nfet Vth > 0

/*
* Update ox cap, update psi_beta -> update Vth -> update op region -> update Ids
*/

class fet
{
   public:
      fet();
      fet(int type);
      fet(int type, float width, float length, float Na, float tox, float MuN);

      float get_drainage_current();
      float get_width();
      float get_length();
      float get_e_mobility();
      float get_cox();
      float get_Vth(); // Threshold voltag: the minimum gate voltage required to induce current
      float get_Cox(); // oxide capacitance
      float get_psi_beta();
      void print_operating_region();

      void set_channel_doping(float Na);
      void set_tox_nm(float tox);
      void set_width_nm(float tox);
      void set_length_nm(float tox);
      void set_gate_voltage(float v);
      void set_drain_voltage(float v);
      void set_mobility(float MuN);

   private:
      int get_operating_region();

      float Na;  // channel doping
      float tox; // in meters
      float width;
      float length;
      float MuN; // mobility of electrons
      int type; // PMOS or NMOS
      float Vgs;
      float Vds;

};

#endif