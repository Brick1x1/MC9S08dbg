#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "hcs08_instruction.h"
#include "sim_MC9S08_S08AC60.h"


#define AM_NA     0x00   // Not a valid opcode
#define AM_DIR    0x01   // Direct addressing mode
#define AM_EXT    0x02   // Extended addressing mode
#define AM_IMM    0x03   // Immediate addressing mode
#define AM_INH    0x04   // Inherent addressing mode
#define AM_IX0    0x05   // Indexed, no offset addressing mode
#define AM_IX1    0x06   // Indexed, 8-bit offset addressing mode
#define AM_IX2    0x07   // Indexed, 16-bit offset addressing mode
#define AM_IXP    0x08   // Indexed, no offset, post increment addressing mode
#define AM_I1P    0x09   // Indexed, 8-bit offset, post increment addressing mode
#define AM_REL    0x0A   // Relative addressing mode
#define AM_SP1    0x0B   // Stack pointer, 8-bit offset addressing mode
#define AM_SP2    0x0C   // Stack pointer 16-bit offset addressing mode


using namespace std;

simMC9S08AC60::simMC9S08AC60(unsigned char *p_memory)
{
   //Copy memory
   memory = (unsigned char *)malloc(0x10000);
   memcpy(memory,p_memory,0x10000);


   //Initialize instructions
   for(int i=0; i < 256; i++) instructions[i] = new hcs08Instruction();
   for(int i=0; i < 256; i++) instructionsExt[i] = new hcs08Instruction();

   char tempInstNoOfBytes[256] = {  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, //0x00
                                    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, //0x10
                                    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, //0x20
                                    2,3,3,2,2,2,2,2,2,2,2,3,2,2,3,2, //0x30
                                    1,3,1,1,1,3,1,1,1,1,1,2,1,1,3,1, //0x40
                                    1,3,1,1,1,2,1,1,1,1,1,2,1,1,2,1, //0x50
                                    2,3,1,2,2,3,2,2,2,2,2,3,2,2,3,2, //0x60
                                    1,2,1,1,1,2,1,1,1,1,1,2,1,1,2,1, //0x70
                                    1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1, //0x80
                                    2,2,2,2,1,1,3,1,1,1,1,1,1,1,0,1, //0x90
                                    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, //0xA0
                                    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, //0xB0
                                    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, //0xC0
                                    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, //0xD0
                                    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, //0xE0
                                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};//0xF0
   for(int i=0;i<256;i++) instructions[i]->noOfBytes = tempInstNoOfBytes[i];
   char tempInstExtNoOfBytes[256] = {  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x00
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x10
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x20
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x30
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x40
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x50
                                       3,4,0,3,3,0,3,3,3,3,3,4,3,3,0,3, //0x60
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x70
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x80
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //0x90
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0, //0xA0
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0, //0xB0
                                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0, //0xC0
                                       4,4,4,4,4,4,4,4,4,4,4,4,0,0,4,4, //0xD0
                                       3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3, //0xE0
                                       0,0,0,3,0,0,0,0,0,0,0,0,0,0,3,3};//0xF0
   for(int i=0;i<256;i++) instructionsExt[i]->noOfBytes = tempInstExtNoOfBytes[i];

   //Addressing mode, 1st mode (mov have to addressing modes)
   char tempInstAddressingMode1st[256] = { AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, //0x00
                                           AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, //0x10
                                           AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, //0x20
                                           AM_DIR, AM_DIR, AM_EXT, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_EXT, AM_DIR, //0x30
                                           AM_INH, AM_IMM, AM_INH, AM_INH, AM_INH, AM_IMM, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_DIR, AM_INH, //0x40
                                           AM_INH, AM_IMM, AM_INH, AM_INH, AM_INH, AM_DIR, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_DIR, AM_INH, //0x50
                                           AM_IX1, AM_I1P, AM_INH, AM_IX1, AM_IX1, AM_IMM, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IMM, AM_IX1, //0x60
                                           AM_IX0, AM_IXP, AM_INH, AM_IX0, AM_IX0, AM_DIR, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IXP, AM_IX0, //0x70
                                           AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_NA , AM_INH, AM_INH, //0x80
                                           AM_REL, AM_REL, AM_REL, AM_REL, AM_INH, AM_INH, AM_EXT, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_NA , AM_INH, //0x90
                                           AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_NA , AM_REL, AM_IMM, AM_IMM, //0xA0
                                           AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, //0xB0
                                           AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, //0xC0
                                           AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, //0xD0
                                           AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, //0xE0
                                           AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0};//0xF0
   for(int i=0;i<256;i++) instructions[i]->addressingMode1st = tempInstAddressingMode1st[i];

   for(int i=0;i<256;i++) instructions[i]->addressingMode2nd = AM_NA;
   instructions[0x4E]->addressingMode2nd = AM_DIR;
   instructions[0x5E]->addressingMode2nd = AM_IXP;
   instructions[0x6E]->addressingMode2nd = AM_DIR;
   instructions[0x7E]->addressingMode2nd = AM_DIR;

   //Addressing mode page 2 (starts with opcode 9E), 1st mode
   char tempInstExtAddressingMode1st[256] = { AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x00
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x10
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x20
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x30
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x40
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x50
                                              AM_SP1, AM_SP1, AM_NA , AM_SP1, AM_SP1, AM_NA , AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_NA , AM_SP1, //0x60
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x70
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x80
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , //0x90
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_IX0, AM_NA , //0xA0
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_IX2, AM_NA , //0xB0
                                              AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_IX1, AM_NA , //0xC0
                                              AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_SP2, AM_NA , AM_NA , AM_SP2, AM_SP2, //0xD0
                                              AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_SP1, AM_NA , AM_NA , AM_SP1, AM_SP1, //0xE0
                                              AM_NA , AM_NA , AM_NA , AM_SP1 , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_SP1, AM_SP1 };//0xF0
   for(int i=0;i<256;i++) instructionsExt[i]->addressingMode1st = tempInstExtAddressingMode1st[i];

   // ------------------------------------------------------------
   //  Remove - Only for debugging purpose
   //
   memory[0x4A] |= 0x08; //Set bit 3 of reg. 'ICGS1'  bit 'LOCK', means: FLL Engaged Internal Locked

   // Before 0x1 and 0x72, bypass loop, which exists at 0x263
   memory[0xF667] = 0x02; memory[0xF668] = 0x5E;

   //Short loop from B8 hex to 4
   memory[0xF6D6] = 0x04;

   // Simulate high on input Port C bit 5, J15_1_ASY_IN (debug port)
   // F6CD BRCLR5 #04 05
   memory[0x0004] |= 0x20;

   // Simulate high on input Port C bit 3, J15_2_ASY_OUT (debug port)
   // F6D0 BRCLR3 #04 02
   //memory[0x0004] |= 0x08;

   // Retry measurement on J15_2_ASY_OUT (debug port) and J15_1_ASY_IN (debug port), from 27 to 2 retries.
   // F6DB  A11B    CMP #1B
   memory[0xF6DC] = 0x02;


   // Unknown - Do not branch in code location F601
   //memory[0xF5FF] = 0x00;


   //
   //  END - Remove - Only for debugging purpose
   // ------------------------------------------------------------



   A = 0; // ACCUMULATOR
   H = 0; // INDEX REGISTER (HIGH)
   X = 0; // INDEX REGISTER (LOW)
   SP = 0; // STACK POINTER
   PC = 0; // PROGRAM COUNTER

   // CONDITION CODE REGISTER
   STATUS_C = 0; // bit 0 - CARRY
   STATUS_Z = 0; // bit 1 - CCR_ZERO
   STATUS_N = 0; // bit 2 - CCR_NEGATIVE
   STATUS_I = 0; // bit 3 - CCR_INTERRUPT_MASK
   STATUS_H = 0; // bit 4 - CCR_HALF_CARRY
   STATUS_V = 0; // bit 7 - CCR_TWO_S_COMPLEMENT_OVERFLOW

   // Fetch reset vector
   PC = memory[0xFFFE] * 0x100 + memory[0xFFFF];

   //Debug
   //PC = 0xF62A; // PROGRAM COUNTER

}


void simMC9S08AC60::setAddressingModeText(unsigned short memory_index)
{
   unsigned char opcode = memory[memory_index];
   char temp_addressingModeText[20];
   //Is opcode extended ?
   if(opcode != 0x9E)
   {
      //Page 1 char addressingMode, unsigned char *buffer)
      if(instructions[opcode]->addressingMode2nd == AM_NA)
      {
         getAddressingModeAsText(instructions[opcode]->addressingMode1st,temp_addressingModeText);
         sprintf(addressingModeText,"%s",temp_addressingModeText);
      }
      else
      {
         char temp_addressingModeText2nd[20];
         getAddressingModeAsText(instructions[opcode]->addressingMode1st,temp_addressingModeText);
         getAddressingModeAsText(instructions[opcode]->addressingMode2nd,temp_addressingModeText2nd);
         sprintf(addressingModeText,"%s/%s ",temp_addressingModeText,temp_addressingModeText2nd);
      }

   }
   else
   {
      //Page two (extended opcodes)
      opcode = memory[memory_index+1];
      getAddressingModeAsText(instructionsExt[opcode]->addressingMode1st,temp_addressingModeText);
      sprintf(addressingModeText,"%s",temp_addressingModeText);
   }

}


void simMC9S08AC60::step()
{
   unsigned char H_temp;
   unsigned char X_temp;
   unsigned char IMM_temp;
   unsigned char ADDR_temp;
   unsigned char PCL_temp,PCH_temp;
   unsigned char RESULT_temp;
   unsigned short INDEX_temp;
   unsigned short MEM_temp;
   unsigned short RESULT_S_temp;
   unsigned char oprx8_temp;
   unsigned short opr16a;
   unsigned char m_temp;
   unsigned char r_temp;
   unsigned char rel_temp;
   unsigned char opr8a_temp;
   unsigned char A7,M7,R7,A3,M3,R3;

   instructionCounter++;

   sprintf(programCounterText,"%04X",PC);


   //write adressing mode text
   setAddressingModeText(PC);

   //Set instruction length
   if(memory[PC] != 0x9E)
      instructionLength = instructions[memory[PC]]->noOfBytes;
   else
      instructionLength = instructionsExt[memory[PC+1]]->noOfBytes;

   //Write bytecode text
   if(memory[PC] != 0x9E)
      setBytecodeText(instructions[memory[PC]]->noOfBytes, memory + PC);
   else
      setBytecodeText(instructionsExt[memory[PC+1]]->noOfBytes, memory + PC);

   PC_previous = PC;

   //opcode
   switch(memory[PC])
   {
      case 0x07: // BRCLR 3,opr8a,rel (DIR-b3) - Branch if Bit 3 in Memory Clear
         PC +=1;
         IMM_temp = memory[PC++];
         sprintf(disassembleText,"BRCLR3 #%02X %02d",IMM_temp,(char)memory[PC]);
         //printf("memory[IMM_temp]: %d\n", memory[IMM_temp]);
         //printf("memory[IMM_temp] & 0x08: %d\n", memory[IMM_temp] & 0x08);
         if(memory[IMM_temp] & 0x08) { //Mask bit 3
            PC += 1;
            STATUS_C = 1;
         }
         else {
            PC = PC + 1 + (char)memory[PC];
            STATUS_C = 0;
         }
         break;

      case 0x0B: // BRCLR 5,opr8a,rel (DIR-b5) - Branch if Bit 5 in Memory Clear
         PC +=1;
         IMM_temp = memory[PC++];
         sprintf(disassembleText,"BRCLR5 #%02X %02d",IMM_temp,(char)memory[PC]);
         //printf("memory[IMM_temp]: %d\n", memory[IMM_temp]);
         //printf("memory[IMM_temp] & 0x08: %d\n", memory[IMM_temp] & 0x08);
         if(memory[IMM_temp] & 0x20) { //Mask bit 5
            PC += 1;
            STATUS_C = 1;
         }
         else {
            PC = PC + 1 + (char)memory[PC];
            STATUS_C = 0;
         }
         break;

      case 0x20: // BRA rel (REL)- Branch Always
         PC++;
         rel_temp = memory[PC++];
         PC = PC + (char)rel_temp;
         sprintf(disassembleText,"BRA %04X",PC);
         break;

      case 0x24: // BCC rel (REL) - Branch if Carry Bit Clear
         PC++;
         rel_temp = memory[PC++];
         sprintf(disassembleText,"BCC #%d",(char)rel_temp);
         if(STATUS_C == 0)
            PC = PC + (char)rel_temp;
         break;


      case 0x25: // BCS rel (REL) - Branch if Carry Bit Set
         sprintf(disassembleText,"BCS #%d",(char)memory[PC+1]);
         if(STATUS_C)
            PC = PC + 2 + (char)memory[PC+1];
         else
            PC += 2;
         break;

      case 0x26: // BNE rel (REL) - Branch if Not Equal
         PC++;
         ADDR_temp = memory[PC++];
         sprintf(disassembleText,"BNE %d",(char)ADDR_temp);
         if(STATUS_Z == 0) {
               PC = PC + (char)ADDR_temp;
         }
         break;

      case 0x27: // BEQ rel (REL) - Branch if Equal
         PC++;
         ADDR_temp = memory[PC++];
         sprintf(disassembleText,"BEQ %d",(char)ADDR_temp);
         if(STATUS_Z == 1) {
               PC = PC + (char)ADDR_temp;
         }
         break;

      case 0x2A: // BPL rel (REL) - Branch if Plus
         PC++;
         ADDR_temp = memory[PC++];
         sprintf(disassembleText,"BPL %d",(char)ADDR_temp);
         if(STATUS_N == 0) {
               PC = PC + (char)ADDR_temp;
         }
         break;

      case 0x32: // LDHX opr16a (EXT) - Load Index Register from Memory
         PC++;
         PCH_temp = memory[PC++];
         PCL_temp = memory[PC++];
         H = memory[PCH_temp * 0x100 + PCL_temp];
         X = memory[PCH_temp * 0x100 + PCL_temp + 1];
         sprintf(disassembleText,"LDHX %04X",PCH_temp * 0x100 + PCL_temp);
         STATUS_V = 0;
         STATUS_N = (H >> 7) & 0x01;
         if(H==0 && X==0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0x35: // STHX opr8a (DIR) - Store Index Register
         PC++;
         opr8a_temp = memory[PC++];
         memory[opr8a_temp] = H;
         memory[opr8a_temp + 1] = X;
         sprintf(disassembleText,"STHX %02X",opr8a_temp);
         STATUS_V = 0;
         STATUS_N = (H >> 7) & 0x01;
         if(H==0 && X==0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0x38: // LSL opr8a (DIR) - Logical Shift Left
         PC++;
         opr8a_temp = memory[PC++];
         m_temp = memory[opr8a_temp];
         sprintf(disassembleText,"LSL %02X",opr8a_temp);
         STATUS_C = (m_temp >> 7) & 0x01;
         RESULT_temp = m_temp << 1;
         STATUS_N = (RESULT_temp >> 7) & 0x01;
         STATUS_V = STATUS_N ^ STATUS_C;
         if(RESULT_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         memory[opr8a_temp] = RESULT_temp;
         break;

      case 0x39: // ROL opr8a (DIR) - Rotate Left through Carry
         PC++;
         opr8a_temp = memory[PC++];
         m_temp = memory[opr8a_temp];
         sprintf(disassembleText,"ROL %02X",opr8a_temp);
         RESULT_temp = (m_temp << 1) + STATUS_C;
         STATUS_C = (m_temp >> 7) & 0x01;
         STATUS_N = (RESULT_temp >> 7) & 0x01;
         STATUS_V = STATUS_N ^ STATUS_C;
         if(RESULT_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         memory[opr8a_temp] = RESULT_temp;
         break;

      case 0x3C: // INC opr8a (DIR) - Increment
         PC++;
         opr8a_temp = memory[PC++];
         RESULT_S_temp = memory[opr8a_temp];
         memory[opr8a_temp] = ++RESULT_S_temp & 0x00FF;
         sprintf(disassembleText,"INC %02X",opr8a_temp);
         if(RESULT_S_temp == 0x80) STATUS_V = 1;else STATUS_V = 0;
         STATUS_N = (RESULT_S_temp >> 7) & 0x01;
         if(RESULT_S_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0x3F: // CLR opr8a (DIR) - Clear
         PC++;
         opr8a_temp = memory[PC++];
         memory[opr8a_temp] = 0;
         sprintf(disassembleText,"CLR %02X",opr8a_temp);
         STATUS_V = 0;
         STATUS_N = 0;
         STATUS_Z = 1;
         break;

      case 0x41: // CBEQA #opr8i,rel  CBEQX #opr8i,rel IMM - Compare and Branch if Equal
         PC++;
         IMM_temp = memory[PC++];
         ADDR_temp = memory[PC++];
         sprintf(disassembleText,"CBEQA %02X,%04X",IMM_temp,PC + (char)ADDR_temp);
         if(IMM_temp == A) {
               PC = PC + (char)ADDR_temp;
         }
         break;

      case 0x44: // LSRA (INH-A) - Logical Shift Right
         PC++;
         sprintf(disassembleText,"LSRA");
         STATUS_V = A & 0x01;
         STATUS_C = A & 0x01;
         A = A >> 1;
         STATUS_N = 0;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0x45: // LDHX #opr16i (IMM)
         PC +=1;
         H = memory[PC++];
         X = memory[PC++];
         sprintf(disassembleText,"LDHX #%04X",H*0x100+X);
         STATUS_V = 0;
         STATUS_N = (H >> 7) & 0x01;
         if(H==0 && X==0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0x48: // LSLA (INH-A) - Logical Shift Left (Same as ASL)
         PC++;
         sprintf(disassembleText,"LSLA");
         STATUS_C = (A >> 7) & 0x01;
         A = A << 1;
         STATUS_N = (A >> 7) & 0x01;
         STATUS_V = STATUS_N ^ STATUS_C;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0x4B: // DBNZA rel (INH) - Decrement and Branch if Not Zero
         PC++;
         ADDR_temp = memory[PC++];
         sprintf(disassembleText,"DBNZA #%d",(char)ADDR_temp);
         A--;
         if(A != 0) {
               PC = PC + (char)ADDR_temp;
         }
         break;

      case 0x4C: // INCA (INH-A) - Increment
         PC++;
         sprintf(disassembleText,"INCA");
         A++;
         if(A == 0x80) STATUS_V = 1; else STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0x4D: // TSTA INH (A) - Test for Negative or Zero
         PC++;
         sprintf(disassembleText,"TSTA");
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0x4F: // CLRA (INH-A) - Clear
         PC +=1;
         A = 0x00;
         sprintf(disassembleText,"CLRA");
         STATUS_V = 0;
         STATUS_N = 0;
         STATUS_Z = 1;
         break;

      case 0x51: // CBEQX #opr8i,rel IMM - Compare and Branch if Equal
         PC++;
         IMM_temp = memory[PC++];
         ADDR_temp = memory[PC++];
         sprintf(disassembleText,"CBEQX %02X,%d",IMM_temp,(char)ADDR_temp);
         if(IMM_temp == X) {
               PC = PC + (char)ADDR_temp;
         }
         break;

      case 0x5D: // TSTX (INH-X) - Test for Negative or Zero
         PC++;
         sprintf(disassembleText,"TSTX");
         STATUS_V = 0;
         STATUS_N = (X >> 7) & 0x01;
         if(X == 0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0x65: // CPHX (IMM) - Compare Index Register with Memory
         INDEX_temp = H * 0x100 + X;
         MEM_temp = memory[PC+1]*0x100 + memory[PC+2];
         PC+=3;

         RESULT_S_temp = (short)INDEX_temp - (short)MEM_temp;

         sprintf(disassembleText,"CPHX #%04X",MEM_temp);

         //V flag - 2's complement overflow
         STATUS_V = ( (H>>7) && !(MEM_temp>>15) && !(RESULT_S_temp>>15)) ||
                    (!(H>>7) &&  (MEM_temp>>15) &&  (RESULT_S_temp>>15));  // H7 & /M15 & /R15 | /H7 & M15 & R15

         STATUS_N = (RESULT_S_temp>>15);

         if(RESULT_S_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;

         if(MEM_temp > INDEX_temp) STATUS_C = 1; else STATUS_C = 0;

         break;

      case 0x6E: // MOV #opr8i,opr8a (IMM/DIR) - Move
         PC +=1;
         IMM_temp = memory[PC++];
         ADDR_temp = memory[PC++];
         memory[ADDR_temp] = IMM_temp;
         sprintf(disassembleText,"MOV #%02X,%02X",IMM_temp,ADDR_temp);
         STATUS_V = 0;
         STATUS_N = (IMM_temp >> 7) & 0x01;
         if(IMM_temp==0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0x7C: // INC - INC ,X (IX) - Increment
         PC++;
         RESULT_S_temp = memory[H*0x100 + X];
         RESULT_S_temp++;
         memory[H*0x100 + X] = RESULT_S_temp;

         if(RESULT_S_temp == 0x80) STATUS_V = 1;
         else STATUS_V = 0;

         STATUS_N = (RESULT_S_temp >> 7) & 0x01;

         if(RESULT_S_temp == 0) STATUS_Z = 1;
         else STATUS_Z = 0;

         sprintf(disassembleText,"INC ,#%04X",H*0x100+X);
         break;

      case 0x7F: // CLR ,X (IX)  - Clear memory pointed to by H:X
         PC++;
         memory[H*0x100 + X] = 0;
         STATUS_V = 0;
         STATUS_N = 0;
         STATUS_Z = 1;
         sprintf(disassembleText,"CLR ,#%04X",H*0x100+X);
         break;

      case 0x81: // RTS (INH) - Return from Subroutine
         PCH_temp = memory[++SP];
         PCL_temp = memory[++SP];
         PC = PCH_temp * 0x100 + PCL_temp;
         sprintf(disassembleText,"RTS #%04X",PC);
         break;

      case 0x84: // TAP (INH) - Transfer Accumulator to Processor Status Byte
         PC +=1;
         STATUS_V = (A & 0x80) >> 7; STATUS_H = (A & 0x10) >> 4; STATUS_I = (A & 0x08) >> 3;
         STATUS_N = (A & 0x04) >> 2; STATUS_Z = (A & 0x02) >> 1; STATUS_C = (A & 0x01);
         sprintf(disassembleText,"TAP");
         break;

      case 0x85: // TPA (INH) - Transfer Processor Status Byte to Accumulator
         PC +=1;
         A = (STATUS_V << 7) + (STATUS_H << 4) + (STATUS_I << 3) + (STATUS_N << 2) + (STATUS_Z << 1) + (STATUS_C) + 0x60;
         sprintf(disassembleText,"TPA");
         break;

      case 0x86: // PULA (INH) - Pull Accumulator from Stack
         PC +=1;
         SP++;
         A = memory[SP];
         sprintf(disassembleText,"PULA");
         break;

      case 0x87: // PSHA (INH) - Push Accumulator onto Stack
         PC +=1;
         memory[SP--] = A;
         sprintf(disassembleText,"PSHA");
         break;

      case 0x88: // PULX (INH) - Pull X (Index Register Low) from Stack
         PC +=1;
         SP++;
         X = memory[SP];
         sprintf(disassembleText,"PULX");
         break;

      case 0x89: // PSHX (INH) - Push X (Index Register Low) onto Stack
         PC += 1;
         memory[SP--] = X;
         sprintf(disassembleText,"PSHX");
         break;

      case 0x8A: // PULH (INH) - Pull H (Index Register High) from Stack
         PC +=1;
         SP++;
         H = memory[SP];
         sprintf(disassembleText,"PULH");
         break;

      case 0x8B: // PSHH (INH) - Push H (Index Register High) onto Stack
         PC += 1;
         memory[SP--] = H;
         sprintf(disassembleText,"PSHH");
         break;

      case 0x94: // TXS (INH) - Transfer Index Register to Stack Pointer
         PC +=1;
         SP = (H*0x100+X)-1;
         sprintf(disassembleText,"TXS");
         break;

      case 0x95: // TSX INH - Transfer Stack Pointer to Index Register
         PC +=1;
         H = ((SP + 1) & 0xFF00 ) >> 8;
         X = ((SP + 1) & 0x00FF );
         sprintf(disassembleText,"TSX");
         break;

      case 0x96: // STHX opr16a (EXT) - Store Index Register
         PC++;
         opr16a  = memory[PC++] * 0x100;
         opr16a += memory[PC++];
         memory[opr16a] = H;
         memory[opr16a + 1] = X;
         sprintf(disassembleText,"STHX %04X",opr16a);
         break;

      case 0x97: // TAX INH - Transfer Accumulator to X (Index Register Low)
         PC +=1;
         X = A;
         sprintf(disassembleText,"TAX");
         break;

      case 0x9B: // SEI Set Interrupt Mask Bit
         PC++;
         sprintf(disassembleText,"SEI");
         STATUS_I = 1;
         break;

      case 0x9D: // NOP (INH) - No Operation
         PC++;
         sprintf(disassembleText,"NOP");
         break;


      case 0x9E: // Page 2
         PC++;
         switch(memory[PC])
         {
            case 0x69: // ROL oprx8,SP (SP1) - Rotate Left through Carry
               PC++;
               oprx8_temp = memory[PC++];
               m_temp = memory[SP + oprx8_temp];
               sprintf(disassembleText,"ROL %04X",SP + oprx8_temp);

               RESULT_temp = (m_temp << 1) + STATUS_C;
               STATUS_C = (m_temp >> 7) & 0x01;
               STATUS_N = (RESULT_temp >> 7) & 0x01;
               STATUS_V = STATUS_N ^ STATUS_C;
               if(RESULT_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
               memory[SP + oprx8_temp] = RESULT_temp;
               break;

            case 0x6B: // DBNZ oprx8,SP,rel (SP1) - Decrement and Branch if Not Zero
               PC++;
               oprx8_temp = memory[PC++];
               rel_temp = memory[PC++];
               memory[SP + oprx8_temp]--;
               MEM_temp = memory[SP + oprx8_temp];

               sprintf(disassembleText,"DBNZ %04X,%d",SP + oprx8_temp,(char)rel_temp);
               MEM_temp--;
               if(MEM_temp != 0) {
                     PC = PC + (char)rel_temp;
               }
               break;

            case 0xAE: // LDHX ,X (IX) - Load Index Register from Memory
               PC++;
               PCH_temp = memory[H * 0x100 + X];
               PCL_temp = memory[H * 0x100 + X + 1];
               sprintf(disassembleText,"LDHX %04X",H * 0x100 + X);
               H = PCH_temp;
               X = PCL_temp;
               STATUS_V = 0;
               STATUS_N = (H >> 7) & 0x01;
               if(H==0 && X==0) STATUS_Z = 1; else STATUS_Z = 0;
               break;

            case 0xCE: // LDHX oprx8,X (IX1) - Load Index Register from Memory
               PC++;
               oprx8_temp = memory[PC++];
               PCH_temp = memory[H * 0x100 + X + oprx8_temp];
               PCL_temp = memory[H * 0x100 + X + oprx8_temp + 1];
               sprintf(disassembleText,"LDHX %04X",H * 0x100 + X + oprx8_temp);
               H = PCH_temp;
               X = PCL_temp;
               STATUS_V = 0;
               STATUS_N = (H >> 7) & 0x01;
               if(H==0 && X==0) STATUS_Z = 1;
               else STATUS_Z = 0;
               break;

            case 0xE1: // CMP oprx8,SP (SP1) - Compare Accumulator with Memory
               PC++;
               oprx8_temp = memory[PC++];
               r_temp = memory[SP + oprx8_temp];

               RESULT_temp = (signed char)A - (signed char)r_temp;

               //V flag - 2's complement overflow
               STATUS_V = ( (A >> 7) && !(r_temp >> 7) && !(RESULT_temp >> 7)) ||
                          (!(A >> 7) &&  (r_temp >> 7) &&  (RESULT_temp >> 7));  // A7 & /M7 & /R7 | /A7 & M7 & /R7

               STATUS_N = (RESULT_temp >> 7);

               if(RESULT_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;

               if(r_temp > A) STATUS_C = 1; else STATUS_C = 0;

               sprintf(disassembleText,"CMP %02X,%04X",oprx8_temp,SP);
               break;


            case 0xE6: // LDA oprx8,SP (SP1) - Load Accumulator from Memory
               PC++;
               oprx8_temp = memory[PC++];
               A = memory[SP + oprx8_temp];
               sprintf(disassembleText,"LDA %04X",SP + oprx8_temp);
               STATUS_V = 0;
               STATUS_N = (A >> 7) & 0x01;
               if(A==0) STATUS_Z = 1; else STATUS_Z = 0;
               break;

            case 0xE7: // STA oprx8,SP (SP1) - Store Accumulator in Memory
               PC++;
               oprx8_temp = memory[PC++];
               memory[SP + oprx8_temp] = A;
               sprintf(disassembleText,"STA %04X",SP + oprx8_temp);
               STATUS_V = 0;
               STATUS_N = (A >> 7) & 0x01;
               if(A==0) STATUS_Z = 1; else STATUS_Z = 0;
               break;

            case 0xF3: // CPHX oprx8,SP (SP1) - Compare Index Register with Memory
               PC++;
               oprx8_temp = memory[PC++];

               sprintf(disassembleText,"CPHX %02X,%04X",oprx8_temp,SP);

               MEM_temp = memory[SP + oprx8_temp] * 100 + memory[SP + oprx8_temp + 1];
               INDEX_temp = H * 0x100 + X;

               RESULT_S_temp = (short)INDEX_temp - (short)MEM_temp;

               //V flag - 2's complement overflow
               STATUS_V = ( (H>>7) && !(MEM_temp>>15) && !(RESULT_S_temp>>15)) ||
                          (!(H>>7) &&  (MEM_temp>>15) &&  (RESULT_S_temp>>15));  // H7 & /M15 & /R15 | /H7 & M15 & R15

               STATUS_N = (RESULT_S_temp>>15);

               if(RESULT_S_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;

               if(MEM_temp > INDEX_temp) STATUS_C = 1; else STATUS_C = 0;

               break;


            case 0xFE: // LDHX oprx8,SP (SP1) - Load Index Register from Memory
               PC++;
               oprx8_temp = memory[PC++];
               PCH_temp = memory[SP + oprx8_temp];
               PCL_temp = memory[SP + oprx8_temp + 1];
               sprintf(disassembleText,"LDHX %02X,%04X",oprx8_temp,SP);
               H = PCH_temp;
               X = PCL_temp;
               STATUS_V = 0;
               STATUS_N = (H >> 7) & 0x01;
               if(H == 0 && X == 0) STATUS_Z = 1; else STATUS_Z = 0;
               break;

            case 0xFF: // STHX oprx8,SP (SP1) - Store Index Register
               PC++;
               oprx8_temp = memory[PC++];
               memory[SP + oprx8_temp] = H;
               memory[SP + oprx8_temp + 1] = X;
               sprintf(disassembleText,"STHX %02X,%04X",oprx8_temp,SP);
               STATUS_V = 0;
               STATUS_N = (H >> 7) & 0x01;
               if(H == 0 && X == 0) STATUS_Z = 1; else STATUS_Z = 0;
               break;

            default:
               sprintf(disassembleText,"Unknown opcode: 9E%02X, inst. count: %d",memory[PC],instructionCounter);
               PC--;
               break;
         }
         break;


      case 0x9F: // TXA (INH) - Transfer X (Index Register Low) to Accumulator
         PC++;
         A = X;
         sprintf(disassembleText,"TXA");
         break;

      case 0xA0: // SUB #opr8i (IMM) - Subtract
         PC++;
         m_temp = memory[PC++];
         sprintf(disassembleText,"SUB #%02X",m_temp);
         r_temp = A - m_temp;
         A7 = (A & 0x80) >> 7; M7 = (m_temp & 0x80) >> 7; R7 = (r_temp & 0x80) >> 7;
         STATUS_V = (A7 && !M7 && !R7) || (!A7 && M7 && R7);  // A7 & !M7 & !R7 | !A7 & M7 & R7 - flag - 2's complement overflow
         STATUS_N = R7;
         if(r_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         STATUS_C = (!A7 && M7) || (M7 && R7) || (R7 && !A7);  // !A7 & M7 | M7 & R7 | R7 & !A7
         A = r_temp;
         break;

      case 0xA1: // CMP #opr8i IMM - Compare Accumulator with Memory
         PC++;
         IMM_temp = memory[PC++];

         RESULT_temp = (signed char)A - (signed char)IMM_temp;

         //V flag - 2's complement overflow
         STATUS_V = ( (A>>7) && !(IMM_temp>>7) && !(RESULT_temp>>7)) ||
                    (!(A>>7) &&  (IMM_temp>>7) &&  (RESULT_temp>>7));  // A7 & /M7 & /R7 | /A7 & M7 & /R7

         STATUS_N = (RESULT_temp >> 7);

         if(RESULT_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;

         if(IMM_temp > A) STATUS_C = 1; else STATUS_C = 0;

         sprintf(disassembleText,"CMP #%02X",IMM_temp);
         break;

      case 0xA4: // AND #opr8i IMM - Logical AND
         PC++;
         IMM_temp = memory[PC++];
         A = A & IMM_temp;
         sprintf(disassembleText,"AND #%02X",IMM_temp);
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0xA5: // BIT #opr8i IMM - Bit Test
         PC++;
         IMM_temp = memory[PC++];
         RESULT_temp = A & IMM_temp;
         sprintf(disassembleText,"BIT #%02X",IMM_temp);
         STATUS_V = 0;
         STATUS_N = (RESULT_temp >> 7) & 0x01;
         if(RESULT_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0xA6: // LDA #opr8i IMM - Load Accumulator from Memory
         PC++;
         IMM_temp = memory[PC++];
         A = IMM_temp;
         sprintf(disassembleText,"LDA #%02X",IMM_temp);
         STATUS_V = 0;
         STATUS_N = (IMM_temp >> 7) & 0x01;
         if(IMM_temp == 0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0xA7: // AIS #opr8i - Add Immediate Value (Signed) to Stack Pointer
         PC++;
         SP += (char)memory[PC];
         sprintf(disassembleText,"AIS #%02d",(char)memory[PC++]);
         break;

      case 0xAA: // ORA #opr8i (IMM) - Inclusive-OR Accumulator and Memory
         PC++;
         IMM_temp = memory[PC++];
         A = A | IMM_temp;
         sprintf(disassembleText,"ORA #%02X",IMM_temp);
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0xAD: // BSR rel (REL) - Branch to Subroutine
         PC++;
         ADDR_temp = memory[PC++];
         memory[SP--] = (PC & 0x00FF);
         memory[SP--] = (PC & 0xFF00) >> 8;
         PC+= (char)ADDR_temp;
         sprintf(disassembleText,"BSR #%04X",PC);
         break;

      case 0xAF: // AIX #opr8i IMM AF - AIX Add Immediate Value (Signed) to Index Register
         PC++;
         INDEX_temp = H*0x100 + X + (char)memory[PC];
         H = (INDEX_temp & 0xFF00) >> 8;
         X = INDEX_temp & 0x00FF;
         sprintf(disassembleText,"AIX #%d",(char)memory[PC++]);
         break;

      case 0xB6: // LDA opr8a (DIR) - Load Accumulator from Memory
         PC++;
         opr8a_temp = memory[PC++];
         A = memory[opr8a_temp];
         sprintf(disassembleText,"LDA %02X",opr8a_temp);
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0xB7: // STA opr8a (DIR) - Store Accumulator in Memory
         PC++;
         opr8a_temp = memory[PC++];
         memory[opr8a_temp] = A;
         sprintf(disassembleText,"STA %02X",opr8a_temp);
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0xC6: // LDA opr16a EXT : Load Accumulator from Memory
         PC ++;
         H_temp = memory[PC++];
         X_temp = memory[PC++];
         A = memory[H_temp * 0x100 + X_temp];
         sprintf(disassembleText,"LDA %04X",H_temp * 0x100 + X_temp);
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A==0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0xC7: // STA opr16a EXT : Store Accumulator in Memory
         PC +=1;
         H_temp = memory[PC++];
         X_temp = memory[PC++];
         memory[H_temp*0x100+X_temp] = A;
         sprintf(disassembleText,"STA #%04X",H_temp*0x100+X_temp);
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A==0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0xCC: // JMP opr16a EXT - Jump
         PC++;
         PCH_temp = memory[PC++];
         PCL_temp = memory[PC++];
         PC = PCH_temp * 0x100 + PCL_temp;
         sprintf(disassembleText,"JMP #%04X",PCH_temp * 0x100 + PCL_temp);
         break;

      case 0xCD: // JSR opr16a EXT - Jump to Subroutine
         PC++;
         PCH_temp = memory[PC++];
         PCL_temp = memory[PC++];
         memory[SP--] = (PC & 0x00FF);
         memory[SP--] = (PC & 0xFF00) >> 8;
         PC = PCH_temp * 0x100 + PCL_temp;
         sprintf(disassembleText,"JSR #%04X",PCH_temp * 0x100 + PCL_temp);
         break;

      case 0xCE: // LDX opr16a EXT - Load X (Index Register Low) from Memory
         PC ++;
         H_temp = memory[PC++];
         X_temp = memory[PC++];
         X = memory[H_temp * 0x100 + X_temp];
         sprintf(disassembleText,"LDX %04X",H_temp * 0x100 + X_temp);
         STATUS_V = 0;
         STATUS_N = (X >> 7) & 0x01;
         if(X == 0) STATUS_Z = 1;
         else STATUS_Z = 0;
         break;

      case 0xE0: // SUB oprx8,X (IX1) - Subtract
         PC++;
         oprx8_temp = memory[PC++];
         m_temp = memory[H * 0x100 + X + oprx8_temp];
         sprintf(disassembleText,"SUB %04X",H*0x100+X+oprx8_temp);
         r_temp = A - m_temp;
         A7 = (A & 0x80) >> 7; M7 = (m_temp & 0x80) >> 7; R7 = (r_temp & 0x80) >> 7;
         STATUS_V = (A7 && !M7 && !R7) || (!A7 && M7 && R7);  // A7 & !M7 & !R7 | !A7 & M7 & R7 - flag - 2's complement overflow
         STATUS_N = R7;
         if(r_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         STATUS_C = (!A7 && M7) || (M7 && R7) || (R7 && !A7);  // !A7 & M7 | M7 & R7 | R7 & !A7
         A = r_temp;
         break;

      case 0xE2: // SBC oprx8,X (IX1) - Subtract with Carry
         PC++;
         oprx8_temp = memory[PC++];
         m_temp = memory[H * 0x100 + X + oprx8_temp];
         sprintf(disassembleText,"SBC %04X",H*0x100+X+oprx8_temp);
         r_temp = A - m_temp - STATUS_C;
         A7 = (A & 0x80) >> 7; M7 = (m_temp & 0x80) >> 7; R7 = (r_temp & 0x80) >> 7;
         STATUS_V = (A7 && !M7 && !R7) || (!A7 && M7 && R7);  // A7 & !M7 & !R7 | !A7 & M7 & R7 - flag - 2's complement overflow
         STATUS_N = R7;
         if(r_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         STATUS_C = (!A7 && M7) || (M7 && R7) || (R7 && !A7);  // !A7 & M7 | M7 & R7 | R7 & !A7
         A = r_temp;
         break;

      case 0xE6: // LDA oprx8,X (IX1) - Load Accumulator from Memory
         PC++;
         oprx8_temp = memory[PC++];
         A = memory[H * 0x100 + X + oprx8_temp];
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         sprintf(disassembleText,"LDA %02X,%04X",oprx8_temp,H * 0x100 + X);
         break;

      case 0xE7: // STA oprx8,X (IX1) - Store Accumulator in Memory
         PC++;
         oprx8_temp = memory[PC++];
         memory[H * 0x100 + X + oprx8_temp] = A;
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         sprintf(disassembleText,"STA %02X,%04X",oprx8_temp,H*0x100+X);
         break;

      case 0xE9: // ADC oprx8,X (IX1) - Add with Carry
         PC++;
         oprx8_temp = memory[PC++];
         m_temp = memory[H * 0x100 + X + oprx8_temp];
         r_temp = A + m_temp + STATUS_C;
         A = r_temp;
         A7 = (A & 0x80) >> 7; M7 = (m_temp & 0x80) >> 7; R7 = (r_temp & 0x80) >> 7;
         A3 = (A & 0x08) >> 3; M3 = (m_temp & 0x08) >> 3; R3 = (r_temp & 0x08) >> 3;
         STATUS_V = (A7 && M7 && !R7) || (!A7 && !M7 && R7);  // A7 & M7 & /R7 | /A7 & /M7 & R7 - flag - 2's complement overflow
         STATUS_H = (A3 && M3) || (M3 && !R3) || (!R3 && A3);  // A3 & M3 | M3 & /R3 | /R3 & A3
         STATUS_N = R7;
         if(r_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         STATUS_C = (A7 && M7) || (M7 && !R7) || (!R7 && A7);  // A7 & M7 | M7 & !R7 | !R7 & A7*/
         sprintf(disassembleText,"ADC %02X,%04X",oprx8_temp,H*0x100+X);
         break;

      case 0xEB: // ADD oprx8,X (IX1) - Add without Carry
         PC++;
         oprx8_temp = memory[PC++];
         m_temp = memory[H * 0x100 + X + oprx8_temp];
         r_temp = A + m_temp;
         A = r_temp;
         A7 = (A & 0x80) >> 7; M7 = (m_temp & 0x80) >> 7; R7 = (r_temp & 0x80) >> 7;
         A3 = (A & 0x08) >> 3; M3 = (m_temp & 0x08) >> 3; R3 = (r_temp & 0x08) >> 3;
         STATUS_V = (A7 && M7 && !R7) || (!A7 && !M7 && R7);  // A7 & M7 & /R7 | /A7 & /M7 & R7 - flag - 2's complement overflow
         STATUS_H = (A3 && M3) || (M3 && !R3) || (!R3 && A3);  // A3 & M3 | M3 & /R3 | /R3 & A3
         STATUS_N = R7;
         if(r_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         STATUS_C = (A7 && M7) || (M7 && !R7) || (!R7 && A7);  // A7 & M7 | M7 & !R7 | !R7 & A7*/
         sprintf(disassembleText,"ADD %02X,%04X",oprx8_temp,H*0x100+X);
         break;

      case 0xEE: // LDX oprx8,X (IX1) - Load X (Index Register Low) from Memory
         PC++;
         oprx8_temp = memory[PC++];
         X_temp = memory[H * 0x100 + X + oprx8_temp];
         STATUS_V = 0;
         STATUS_N = (X_temp >> 7) & 0x01;
         if(X_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         sprintf(disassembleText,"LDX %02X,%04X",oprx8_temp,H * 0x100 + X);
         X = X_temp;
         break;

      case 0xF2: // SBC oprx8,X (IX) - Subtract with Carry
         PC++;
         m_temp = memory[H * 0x100 + X];
         sprintf(disassembleText,"SBC %04X",H*0x100+X);
         r_temp = A - m_temp - STATUS_C;
         A7 = (A & 0x80) >> 7; M7 = (m_temp & 0x80) >> 7; R7 = (r_temp & 0x80) >> 7;
         STATUS_V = (A7 && !M7 && !R7) || (!A7 && M7 && R7);  // A7 & !M7 & !R7 | !A7 & M7 & R7 - flag - 2's complement overflow
         STATUS_N = R7;
         if(r_temp == 0) STATUS_Z = 1; else STATUS_Z = 0;
         STATUS_C = (!A7 && M7) || (M7 && R7) || (R7 && !A7);  // !A7 & M7 | M7 & R7 | R7 & !A7
         A = r_temp;
         break;

      case 0xF6: // LDA ,X (IX) - Load Accumulator from Memory
         PC++;
         A = memory[H * 0x100 + X];
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         sprintf(disassembleText,"LDA ,#%04X",H*0x100+X);
         break;

      case 0xF7: // STA ,X (IX) - Store Accumulator in Memory
         PC++;
         INDEX_temp = H * 0x100 + X;
         memory[INDEX_temp] = A;
         sprintf(disassembleText,"STA ,%04X",INDEX_temp);
         STATUS_V = 0;
         STATUS_N = (A >> 7) & 0x01;
         if(A == 0) STATUS_Z = 1; else STATUS_Z = 0;
         break;

      case 0xFC: // JMP ,X IX - Jump
         PC++;
         PC = H * 0x100 + X;
         sprintf(disassembleText,"JMP %04X",H * 0x100 + X);
         break;


      case 0xFD: // JSR ,X (IX) - Jump to Subroutine
         PC++;
         memory[SP--] = (PC & 0x00FF);
         memory[SP--] = (PC & 0xFF00) >> 8;
         PC = H * 0x100 + X;
         sprintf(disassembleText,"JSR %04X",H * 0x100 + X);
         break;

      default:
         sprintf(disassembleText,"Unknown opcode: %X, inst. count: %d",memory[PC],instructionCounter);
         break;

   }
}

void simMC9S08AC60::setBytecodeText(char numOfBytes, unsigned char *buffer)
{
   for(int i=0;i<numOfBytes;i++)
      sprintf(bytecodeText + (i * 2),"%02X",buffer[i]);
}


char *simMC9S08AC60::getBytecodeText()
{
   return bytecodeText;
}

char *simMC9S08AC60::getAddressingModeText()
{
   return addressingModeText;
}

char *simMC9S08AC60::getProgramCounterAsText()
{
   return programCounterText;
}

unsigned short simMC9S08AC60::getProgramCounterPrevious()
{
   return PC_previous;
}


char *simMC9S08AC60::getDisassemblyText()
{
   return disassembleText;
}

char *simMC9S08AC60::getConditionCodeRegisterText()
{
   sprintf(conditionCodeRegisterText,"CCR: V:%d H:%d I:%d N:%d Z:%d C:%d",
      STATUS_V,
      STATUS_H,
      STATUS_I,
      STATUS_N,
      STATUS_Z,
      STATUS_C);
   return conditionCodeRegisterText;
}

char *simMC9S08AC60::getCPURegisterText()
{
   sprintf(cpuRegisterText,"A:%02X H:%02X X:%02X SP:%04X PC:%04X",A,H,X,SP,PC);
   return cpuRegisterText;
}

int simMC9S08AC60::getInstructionLength()
{
   return instructionLength;
}

void simMC9S08AC60::getAddressingModeAsText(char addressingMode, char *buffer)
{
   switch(addressingMode)
   {
         case AM_NA : strcpy(buffer,"N/A" ); break;   // Not a valid opcode
         case AM_DIR: strcpy(buffer,"DIR" ); break;   // Direct addressing mode
         case AM_EXT: strcpy(buffer,"EXT" ); break;   // Extended addressing mode
         case AM_IMM: strcpy(buffer,"IMM" ); break;   // Immediate addressing mode
         case AM_INH: strcpy(buffer,"INH" ); break;   // Inherent addressing mode
         case AM_IX0: strcpy(buffer,"IX"  ); break;   // Indexed, no offset addressing mode
         case AM_IX1: strcpy(buffer,"IX1" ); break;   // Indexed, 8-bit offset addressing mode
         case AM_IX2: strcpy(buffer,"IX2" ); break;   // Indexed, 16-bit offset addressing mode
         case AM_IXP: strcpy(buffer,"IX+" ); break;   // Indexed, no offset, post increment addressing mode
         case AM_REL: strcpy(buffer,"REL" ); break;   // Relative addressing mode
         case AM_SP1: strcpy(buffer,"SP1" ); break;   // Stack pointer, 8-bit offset addressing mode
         case AM_SP2: strcpy(buffer,"SP2" ); break;   // Stack pointer 16-bit offset addressing mode
         default: strcpy(buffer,"FAIl" ); break;
   }
}




simMC9S08AC60::~simMC9S08AC60()
{
   //Delete memory
   delete(memory);
}
