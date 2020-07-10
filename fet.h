#ifndef FET_H
#define FET_H

#define SUBTHRESHOLD 1
#define LINEAR 2
#define SATURATION 3

#define PFET 0
#define NFET 1

class fet
{
   public:
      fet();
      fet(float width, float length, float Na, float tox, float MuN);

      float get_drainage_current();
      float get_width();
      float get_length();
      float get_e_mobility();
      float get_cox();
      float get_Vth(); // Threshold voltag: the minimum gate voltage required to induce current
      float get_Cox(); // oxide capacitance
      float get_Vgs();
      float get_Vds();
      float get_psi_beta();
      void print_operating_region();
      // TODO get_depletion() (Lecture 8)

      void set_channel_doping(float Na);
      void set_tox_nm(float tox);
      void set_width_nm(float tox);
      void set_length_nm(float tox);
      void set_gate_voltage(float v);
      void set_drain_voltage(float v);
      void set_mobility(float MuN);

   private:
      virtual int get_operating_region() = 0;

      float Na;  // channel doping
      float tox; // in meters
      float width;
      float length;
      float MuN; // mobility of electrons
      float Vgs;
      float Vds;

};

class pfet: public fet
{
   public:
      int get_operating_region();

};

class nfet: public fet
{
   public:
      int get_operating_region();
};

#endif