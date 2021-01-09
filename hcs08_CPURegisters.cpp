#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "hcs08_CPURegisters.h"

using namespace std;

hcs08CPURegisters::hcs08CPURegisters()
{
}

unsigned char hcs08CPURegisters::getCCR()
{
   return (STATUS_V << 7) + 0x60 + (STATUS_H << 4) + (STATUS_I << 3) + (STATUS_N << 2) + (STATUS_Z << 1) + (STATUS_C);
}

void hcs08CPURegisters::setCCR(unsigned char CCR)
{
   STATUS_V = (CCR & 0x80) >> 7; // bit 7 - CCR_TWO_S_COMPLEMENT_OVERFLOW
   STATUS_H = (CCR & 0x10) >> 4; // bit 4 - CCR_HALF_CARRY
   STATUS_I = (CCR & 0x08) >> 3; // bit 3 - CCR_INTERRUPT_MASK
   STATUS_N = (CCR & 0x04) >> 2; // bit 2 - CCR_NEGATIVE
   STATUS_Z = (CCR & 0x02) >> 1; // bit 1 - CCR_ZERO
   STATUS_C = (CCR & 0x01);      // bit 0 - CARRY
}

void hcs08CPURegisters::getCCRAsText(char *strReturn)
{
   sprintf(strReturn,"CCR: V:%d H:%d I:%d N:%d Z:%d C:%d",
      STATUS_V,
      STATUS_H,
      STATUS_I,
      STATUS_N,
      STATUS_Z,
      STATUS_C);
}

void hcs08CPURegisters::getRegistersAsText(char *strReturn)
{
   sprintf(strReturn,"A:%02X H:%02X X:%02X SP:%04X PC:%04X",A,H,X,SP,PC);
}


unsigned short hcs08CPURegisters::getIndexReg()
{
      return H * 256 + X;
}

void hcs08CPURegisters::setIndexReg(unsigned short indexReg)
{
   H = (indexReg & 0xFF00) >> 8;
   X = indexReg & 0x00FF;
}
