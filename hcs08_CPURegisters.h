#ifndef HCS08_CPUREGISTERS_H
#define HCS08_CPUREGISTERS_H

using namespace std;

class hcs08CPURegisters
{
   public:

      hcs08CPURegisters();

      // PROGRAM COUNTER
      unsigned short PC;

      // ACCUMULATOR
      unsigned char A;

      // INDEX REGISTER (HIGH)
      unsigned char H;

      // INDEX REGISTER (LOW)
      unsigned char X;

      // STACK POINTER
      unsigned short SP;


      // CONDITION CODE REGISTER (CCR)
      unsigned char STATUS_C; // bit 0 - CARRY
      unsigned char STATUS_Z; // bit 1 - CCR_ZERO
      unsigned char STATUS_N; // bit 2 - CCR_NEGATIVE
      unsigned char STATUS_I; // bit 3 - CCR_INTERRUPT_MASK
      unsigned char STATUS_H; // bit 4 - CCR_HALF_CARRY
      unsigned char STATUS_V; // bit 7 - CCR_TWO_S_COMPLEMENT_OVERFLOW

      unsigned char getCCR();
      void setCCR(unsigned char CCR);
      void getCCRAsText(char *strReturn);
      void getRegistersAsText(char *strReturn);

      unsigned short getIndexReg();
      void setIndexReg(unsigned short index);

   private:

};
#endif // HCS08_CPUREGISTERS.H
