//#include "nfet.cc"

#define SUBTHRESHOLD 1
#define LINEAR 2
#define SATURATION 3

class nfet
{
   public:
      float get_threshold_voltage();
      float get_drainage_current();

      void set_channel_doping(float Na);
      void set_tox_nm(float tox);
      void set_width_nm(float tox);
      void set_length_nm(float tox);
      void set_gate_voltage(float v);
      void set_drain_voltage(float v);
      void set_mobility(float MuN);
      //subthreshold condition
      //vgs
      //channel dodping
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

      // derived
      float Cox;
      float psi_beta;
      float Vth; // minimum gate voltage required to induce current
      float Vgs;
      float Vds;
      float drainage_current;
      // float depletion_width;
      int operating_region; // depends on Vth, Vds, Vgs
};