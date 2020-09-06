#ifndef SIM_MC9S08_S08AC60_H
#define SIM_MC9S08_S08AC60_H

#include "hcs08_instruction.h"

using namespace std;

class simMC9S08AC60
{
   public:

      simMC9S08AC60(unsigned char *p_memory);
      ~simMC9S08AC60();
      char *getProgramCounterText();
      char *getBytecodeText();
      char *getAddressingModeText();
      char *getDisassemblyText();
      char *getConditionCodeRegisterText();
      char *getCPURegisterText();
      //int ReadS19File(string filename,unsigned char *memory);

      void step();

      // PROGRAM COUNTER
      unsigned short PC;

      unsigned char *memory;
      /*int HexcharToInt(char ch);
      int ReadInt16Bit(string str,int pos);
      int ReadInt8Bit(string str,int pos);*/

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


   private:

      void setBytecodeText(char numOfBytes, unsigned char *buffer);
      void setAddressingModeText(unsigned short memory_index);

      char programCounterText[100];
      char bytecodeText[20];
      char addressingModeText[20];
      char disassembleText[100];
      char conditionCodeRegisterText[100];
      char cpuRegisterText[50];

      void getAddressingModeAsText(char addressingMode, char *buffer);

      hcs08Instruction *instructions[256];
      hcs08Instruction *instructionsExt[256];
};


#endif // sim_MC9S08_S08AC60_H
