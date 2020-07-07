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

      float get_threshold_voltage();
      float get_drainage_current();
      float get_width();
      float get_length();
      float get_e_mobility();
      float get_cox();

      void set_channel_doping(float Na);
      void set_tox_nm(float tox);
      void set_width_nm(float tox);
      void set_length_nm(float tox);
      void set_gate_voltage(float v);
      void set_drain_voltage(float v);
      void set_mobility(float MuN);
      void set_new_threshold_voltage(float Vth); // manipulates channel doping to achieve desired threshold voltage

   private:
      void update_drainage_current();
      void update_psi_beta();
      void update_threshold_voltage();
      //void update_depletion_width();
      void update_operating_region();
      void update_oxide_capacitance();

      // given
      float Na;  // channel doping
      float tox; // in meters
      float width;
      float length;
      float MuN; // mobility of electrons
      int type; // PMOS or NMOS
      float Vgs;
      float Vds;

      // derived
      float Cox;
      float psi_beta;
      float Vth; // minimum gate voltage required to induce current
      float drainage_current;
      // float depletion_width;
      int operating_region; // depends on Vth, Vds, Vgs
};

#endif