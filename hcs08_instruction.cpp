#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "sim_MC9S08_S08AC60.h"
#include "hcs08_instruction.h"
#include "hcs08_CPURegisters.h"

using namespace std;

hcs08Instruction::hcs08Instruction(unsigned char p_opCode, unsigned char *p_memory, char p_noOfBytes, char p_extendedBytes, char p_addressingMode, hcs08CPURegisters *p_CPURegisters, unsigned char p_InstMnemonic, unsigned char p_MnemonicFlagsMethod, const char *p_MnemonicString, unsigned char p_disassembleFunction)
{
   opCode = p_opCode;
   memory = p_memory;
   noOfBytes = p_noOfBytes;
   extendedBytes = p_extendedBytes;
   addressingMode = p_addressingMode;
   CPURegisters = p_CPURegisters;
   InstMnemonic = p_InstMnemonic;

   strcpy(MnemonicString,p_MnemonicString);

   switch(p_InstMnemonic)
   {
      case IM_NA    : mnemonicOperation = &hcs08Instruction::mnemonicOperationNA;    break;
      case IM_BRSET : mnemonicOperation = &hcs08Instruction::mnemonicOperationBRSET; break;
      case IM_BRCLR : mnemonicOperation = &hcs08Instruction::mnemonicOperationBRCLR; break;
      case IM_BSET  : mnemonicOperation = &hcs08Instruction::mnemonicOperationBSET;  break;
      case IM_BCLR  : mnemonicOperation = &hcs08Instruction::mnemonicOperationBCLR;  break;
      case IM_BRA   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBRA;   break;
      case IM_BRN   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBRN;   break;
      case IM_BHI   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBHI;   break;
      case IM_BLS   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBLS;   break;
      case IM_BCC   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBCC;   break;
      case IM_BCS   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBCS;   break;
      case IM_BNE   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBNE;   break;
      case IM_BEQ   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBEQ;   break;
      case IM_BHCC  : mnemonicOperation = &hcs08Instruction::mnemonicOperationBHCC;  break;
      case IM_BHCS  : mnemonicOperation = &hcs08Instruction::mnemonicOperationBHCS;  break;
      case IM_BPL   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBPL;   break;
      case IM_BMI   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBMI;   break;
      case IM_BMC   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBMC;   break;
      case IM_BMS   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBMS;   break;
      case IM_BIL   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBIL;   break;
      case IM_BIH   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBIH;   break;
      case IM_NEG   : mnemonicOperation = &hcs08Instruction::mnemonicOperationNEG;   break;
      case IM_CBEQ  : mnemonicOperation = &hcs08Instruction::mnemonicOperationCBEQ;  break;
      case IM_LDHX  : mnemonicOperation = &hcs08Instruction::mnemonicOperationLDHX;  break;
      case IM_COM   : mnemonicOperation = &hcs08Instruction::mnemonicOperationCOM;   break;
      case IM_LSR   : mnemonicOperation = &hcs08Instruction::mnemonicOperationLSR;   break;
      case IM_STHX  : mnemonicOperation = &hcs08Instruction::mnemonicOperationSTHX;  break;
      case IM_ROR   : mnemonicOperation = &hcs08Instruction::mnemonicOperationROR;   break;
      case IM_ASR   : mnemonicOperation = &hcs08Instruction::mnemonicOperationASR;   break;
      case IM_LSL   : mnemonicOperation = &hcs08Instruction::mnemonicOperationLSL;   break;
      case IM_ROL   : mnemonicOperation = &hcs08Instruction::mnemonicOperationROL;   break;
      case IM_DEC   : mnemonicOperation = &hcs08Instruction::mnemonicOperationDEC;   break;
      case IM_DBNZ  : mnemonicOperation = &hcs08Instruction::mnemonicOperationDBNZ;  break;
      case IM_INC   : mnemonicOperation = &hcs08Instruction::mnemonicOperationINC;   break;
      case IM_TST   : mnemonicOperation = &hcs08Instruction::mnemonicOperationTST;   break;
      case IM_CPHX  : mnemonicOperation = &hcs08Instruction::mnemonicOperationCPHX;  break;
      case IM_MOV   : mnemonicOperation = &hcs08Instruction::mnemonicOperationMOV;   break;
      case IM_CLR   : mnemonicOperation = &hcs08Instruction::mnemonicOperationCLR;   break;
      case IM_MUL   : mnemonicOperation = &hcs08Instruction::mnemonicOperationMUL;   break;
      case IM_DIV   : mnemonicOperation = &hcs08Instruction::mnemonicOperationDIV;   break;
      case IM_NSA   : mnemonicOperation = &hcs08Instruction::mnemonicOperationNSA;   break;
      case IM_DAA   : mnemonicOperation = &hcs08Instruction::mnemonicOperationDAA;   break;
      case IM_RTI   : mnemonicOperation = &hcs08Instruction::mnemonicOperationRTI;   break;
      case IM_RTS   : mnemonicOperation = &hcs08Instruction::mnemonicOperationRTS;   break;
      case IM_BGND  : mnemonicOperation = &hcs08Instruction::mnemonicOperationBGND; break;
      case IM_SWI   : mnemonicOperation = &hcs08Instruction::mnemonicOperationSWI ; break;
      case IM_TAP   : mnemonicOperation = &hcs08Instruction::mnemonicOperationTAP;   break;
      case IM_TPA   : mnemonicOperation = &hcs08Instruction::mnemonicOperationTPA;   break;
      case IM_PUL   : mnemonicOperation = &hcs08Instruction::mnemonicOperationPUL;   break;
      case IM_PSH   : mnemonicOperation = &hcs08Instruction::mnemonicOperationPSH;   break;
      case IM_STOP  : mnemonicOperation = &hcs08Instruction::mnemonicOperationSTOP;  break;
      case IM_WAIT  : mnemonicOperation = &hcs08Instruction::mnemonicOperationWAIT;  break;
      case IM_BGE   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBGE;   break;
      case IM_BLT   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBLT;   break;
      case IM_BGT   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBGT;   break;
      case IM_BLE   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBLE;   break;
      case IM_TXS   : mnemonicOperation = &hcs08Instruction::mnemonicOperationTXS;   break;
      case IM_TSX   : mnemonicOperation = &hcs08Instruction::mnemonicOperationTSX;   break;
      case IM_TAX   : mnemonicOperation = &hcs08Instruction::mnemonicOperationTAX;   break;
      case IM_CLC   : mnemonicOperation = &hcs08Instruction::mnemonicOperationCLC;   break;
      case IM_SEC   : mnemonicOperation = &hcs08Instruction::mnemonicOperationSEC;   break;
      case IM_CLI   : mnemonicOperation = &hcs08Instruction::mnemonicOperationCLI;   break;
      case IM_SEI   : mnemonicOperation = &hcs08Instruction::mnemonicOperationSEI;   break;
      case IM_RSP   : mnemonicOperation = &hcs08Instruction::mnemonicOperationRSP;   break;
      case IM_NOP   : mnemonicOperation = &hcs08Instruction::mnemonicOperationNOP;   break;
      case IM_PAGE2 : mnemonicOperation = &hcs08Instruction::mnemonicOperationPAGE2; break;
      case IM_TXA   : mnemonicOperation = &hcs08Instruction::mnemonicOperationTXA;   break;
      case IM_SUB   : mnemonicOperation = &hcs08Instruction::mnemonicOperationSUB;   break;
      case IM_CMP   : mnemonicOperation = &hcs08Instruction::mnemonicOperationCMP;   break;
      case IM_SBC   : mnemonicOperation = &hcs08Instruction::mnemonicOperationSBC;   break;
      case IM_CPX   : mnemonicOperation = &hcs08Instruction::mnemonicOperationCPX;   break;
      case IM_AND   : mnemonicOperation = &hcs08Instruction::mnemonicOperationAND;   break;
      case IM_BIT   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBIT;   break;
      case IM_LDA   : mnemonicOperation = &hcs08Instruction::mnemonicOperationLDA;   break;
      case IM_AIS   : mnemonicOperation = &hcs08Instruction::mnemonicOperationAIS;   break;
      case IM_STA   : mnemonicOperation = &hcs08Instruction::mnemonicOperationSTA;   break;
      case IM_EOR   : mnemonicOperation = &hcs08Instruction::mnemonicOperationEOR;   break;
      case IM_ADC   : mnemonicOperation = &hcs08Instruction::mnemonicOperationADC;   break;
      case IM_ORA   : mnemonicOperation = &hcs08Instruction::mnemonicOperationORA;   break;
      case IM_ADD   : mnemonicOperation = &hcs08Instruction::mnemonicOperationADD;   break;
      case IM_JMP   : mnemonicOperation = &hcs08Instruction::mnemonicOperationJMP;   break;
      case IM_BSR   : mnemonicOperation = &hcs08Instruction::mnemonicOperationBSR;   break;
      case IM_JSR   : mnemonicOperation = &hcs08Instruction::mnemonicOperationJSR;   break;
      case IM_LDX   : mnemonicOperation = &hcs08Instruction::mnemonicOperationLDX;   break;
      case IM_STX   : mnemonicOperation = &hcs08Instruction::mnemonicOperationSTX;   break;
      case IM_AIX   : mnemonicOperation = &hcs08Instruction::mnemonicOperationAIX;   break;
      default: mnemonicOperation = nullptr; break;
   }

   switch(p_addressingMode)
   {
         case AM_IMM: setOperandAddress = &hcs08Instruction::setAddressIMM; break;
         case AM_DIR: setOperandAddress = &hcs08Instruction::setAddressDIR; break;
         case AM_REL: setOperandAddress = &hcs08Instruction::setAddressREL; break;
         case AM_EXT: setOperandAddress = &hcs08Instruction::setAddressEXT; break;
         case AM_IX0: setOperandAddress = &hcs08Instruction::setAddressIX0; break;
         case AM_IXP: setOperandAddress = &hcs08Instruction::setAddressIXP; break;
         case AM_IX1: setOperandAddress = &hcs08Instruction::setAddressIX1; break;
         case AM_I1P: setOperandAddress = &hcs08Instruction::setAddressI1P; break;
         case AM_IX2: setOperandAddress = &hcs08Instruction::setAddressIX2; break;
         case AM_SP1: setOperandAddress = &hcs08Instruction::setAddressSP1; break;
         case AM_SP2: setOperandAddress = &hcs08Instruction::setAddressSP2; break;
         default: setOperandAddress = nullptr; break;
   }

   switch(p_disassembleFunction)
   {
         case DF_INH: disassembleTextFunction = &hcs08Instruction::disassembleTextINH;       strcpy(addressingModeAsText,"INH" ); break;
         case DF_IMM8: disassembleTextFunction = &hcs08Instruction::disassembleTextIMM8;     strcpy(addressingModeAsText,"IMM8" ); break;
         case DF_IMM16: disassembleTextFunction = &hcs08Instruction::disassembleTextIMM16;   strcpy(addressingModeAsText,"IMM16" ); break;
         case DF_DIR: disassembleTextFunction = &hcs08Instruction::disassembleTextDIR;       strcpy(addressingModeAsText,"DIR" ); break;
         case DF_DIRREL: disassembleTextFunction = &hcs08Instruction::disassembleTextDIRREL; strcpy(addressingModeAsText,"DIR,REL" ); break;
         case DF_REL: disassembleTextFunction = &hcs08Instruction::disassembleTextREL;       strcpy(addressingModeAsText,"REL" ); break;
         case DF_EXT: disassembleTextFunction = &hcs08Instruction::disassembleTextEXT;       strcpy(addressingModeAsText,"EXT" ); break;
         case DF_IX0: disassembleTextFunction = &hcs08Instruction::disassembleTextIX0;       strcpy(addressingModeAsText,"IX" ); break;
         case DF_IXP: disassembleTextFunction = &hcs08Instruction::disassembleTextIXP;       strcpy(addressingModeAsText,"IX+" ); break;
         case DF_IX1: disassembleTextFunction = &hcs08Instruction::disassembleTextIX1;       strcpy(addressingModeAsText,"IX1" ); break;
         case DF_I1P: disassembleTextFunction = &hcs08Instruction::disassembleTextI1P;       strcpy(addressingModeAsText,"IX1+" ); break;
         case DF_IX2: disassembleTextFunction = &hcs08Instruction::disassembleTextIX2;       strcpy(addressingModeAsText,"IX2" ); break;
         case DF_SP1: disassembleTextFunction = &hcs08Instruction::disassembleTextSP1;       strcpy(addressingModeAsText,"SP1" ); break;
         case DF_SP2: disassembleTextFunction = &hcs08Instruction::disassembleTextSP2;       strcpy(addressingModeAsText,"SP2" ); break;
         case DF_DIRDIR: disassembleTextFunction = &hcs08Instruction::disassembleTextDIRDIR; strcpy(addressingModeAsText,"DIR,DIR" ); break;
         case DF_DIRIXP: disassembleTextFunction = &hcs08Instruction::disassembleTextDIRIXP; strcpy(addressingModeAsText,"DIR,IX+" ); break;
         case DF_IMMDIR: disassembleTextFunction = &hcs08Instruction::disassembleTextIMMDIR; strcpy(addressingModeAsText,"IMM,DIR" ); break;
         case DF_IXPDIR: disassembleTextFunction = &hcs08Instruction::disassembleTextIXPDIR; strcpy(addressingModeAsText,"IX+,DIR" ); break;
         case DF_IMMREL: disassembleTextFunction = &hcs08Instruction::disassembleTextIMMREL; strcpy(addressingModeAsText,"IMM,REL" ); break;
         case DF_I1PREL: disassembleTextFunction = &hcs08Instruction::disassembleTextI1PREL; strcpy(addressingModeAsText,"IX1+,REL" ); break;
         case DF_IXPREL: disassembleTextFunction = &hcs08Instruction::disassembleTextIXPREL; strcpy(addressingModeAsText,"IX+,REL" ); break;
         case DF_SP1REL: disassembleTextFunction = &hcs08Instruction::disassembleTextSP1REL; strcpy(addressingModeAsText,"SP1,REL" ); break;
         case DF_INHREL: disassembleTextFunction = &hcs08Instruction::disassembleTextINHREL; strcpy(addressingModeAsText,"INH,REL" ); break;
         case DF_IX0REL: disassembleTextFunction = &hcs08Instruction::disassembleTextIX0REL; strcpy(addressingModeAsText,"IX,REL" ); break;
         case DF_IX1REL: disassembleTextFunction = &hcs08Instruction::disassembleTextIX1REL; strcpy(addressingModeAsText,"IX1,REL" ); break;
         default:     disassembleTextFunction = nullptr;                                     strcpy(addressingModeAsText,"N/A" );break;
   }


   switch(p_MnemonicFlagsMethod)
   {
         case MFM_VNZ_8B:        setFlags = &hcs08Instruction::setFlagMethodVNZ8B; break;
         case MFM_VNZ_16B:       setFlags = &hcs08Instruction::setFlagMethodVNZ16B; break;
         case MFM_VHNZC_ADD_8B:  setFlags = &hcs08Instruction::setFlagMethodVHNZC_ADD_8B; break;
         case MFM_VNZC_SUB_8B:   setFlags = &hcs08Instruction::setFlagMethodVHNZC_SUB_8B; break;
         case MFM_VNZ_INC_8B:    setFlags = &hcs08Instruction::setFlagMethodVNZ_INC_8B; break;
         case MFM_VNZ_DEC_8B:    setFlags = &hcs08Instruction::setFlagMethodVNZ_DEC_8B; break;
         case MFM_VNZC_CPHX_16B: setFlags = &hcs08Instruction::setFlagMethodVNZC_CPHX_16B; break;
         case MFM_NZ_8B:         setFlags = &hcs08Instruction::setFlagMethodNZ8B; break;
         default: setFlags = nullptr; break;
   }

}

void hcs08Instruction::getBytecodeText(char* str)
{
   int i=0;
   int numOfBytes = noOfBytes;
   if(extendedBytes > 0) numOfBytes++;

   for(;i<numOfBytes;i++)
      sprintf(str + (i * 3),"%02X ",memory[CPURegisters->PC + i]);

   str[(i*3) + 2] = 0;
}

void hcs08Instruction::getAddressingModeAsText(char *str)
{
   strcpy(str,addressingModeAsText);
}

char hcs08Instruction::getInstructionLength()
{
   return noOfBytes + extendedBytes;
}

void hcs08Instruction::Execute()
{
   //printf("PC: %X\n",CPURegisters->PC);

   //printf("%s\n",MnemonicString);


   //If instruction execution changes it to greater than one jump to this address, instead of next address
   AlteredNextAddress = -1;

   //Get address of operand
   if(setOperandAddress != nullptr)
   {
      (this->*setOperandAddress)();
      //printf("operandAddress: %X\n",operandAddress);
   }

   if(mnemonicOperation != nullptr)
   {
      (this->*mnemonicOperation)();
   }

   //printf("InstMnemonic: %i\n",InstMnemonic);

   if(setFlags != nullptr)
   {
      (this->*setFlags)();
   }

   //JMP and branch instructions sets an altered address
   if(AlteredNextAddress > -1)
   {
      CPURegisters->PC = (unsigned short)AlteredNextAddress;
   }
   else
   {
      CPURegisters->PC += (noOfBytes + extendedBytes);
   }

   //printf("Next instruction address (PC): %X\n",CPURegisters->PC);

}


void hcs08Instruction::DisassembleText(char *disassemblyText)
{
   (this->*disassembleTextFunction)(disassemblyText);
}

// ------------------------------------
//
//    Addressing modes
//
// ------------------------------------
void hcs08Instruction::setAddressIMM()
{
      operandAddress = CPURegisters->PC + 1;
      //printf("set operand address IMM\n");
}

void hcs08Instruction::setAddressDIR()
{
      operandAddress = memory[CPURegisters->PC + 1];
      //printf("set operand address DIR\n");
}

void hcs08Instruction::setAddressREL()
{
      char relativOffset = memory[CPURegisters->PC + 1];
      operandAddress = CPURegisters->PC + noOfBytes + relativOffset;
      //printf("set operand address REL\n");
}

void hcs08Instruction::setAddressEXT()
{
   operandAddress = memory[CPURegisters->PC + 1] * 0x100 + memory[CPURegisters->PC + 2];
   //printf("set operand address EXT\n");
}

void hcs08Instruction::setAddressIX0()
{
   operandAddress = CPURegisters->H * 0x100 + CPURegisters->X;
   //printf("set operand address IX0\n");
}

void hcs08Instruction::setAddressIXP()
{
   unsigned short Index = CPURegisters->H * 0x100 + CPURegisters->X;
   operandAddress = Index;
   Index++;
   CPURegisters->H = (Index & 0xFF00) >> 8;
   CPURegisters->X = Index & 0x00FF;
   //printf("set operand address IXP\n");
   //printf("H: %X, X: %X\n",CPURegisters->H,CPURegisters->X);
}

void hcs08Instruction::setAddressIX1()
{
   operandAddress = CPURegisters->H * 0x100 + CPURegisters->X + memory[CPURegisters->PC + 1 + extendedBytes];
   //printf("set operand address IX1\n");
}

void hcs08Instruction::setAddressI1P()
{
   unsigned short Index = CPURegisters->H * 0x100 + CPURegisters->X + memory[CPURegisters->PC + 1 + extendedBytes];
   operandAddress = Index;
   Index++;
   CPURegisters->H = (Index & 0xFF00) >> 8;
   CPURegisters->X = Index & 0x00FF;
   //printf("set operand address I1P\n");
   //printf("H: %X, X: %X\n",CPURegisters->H,CPURegisters->X);
}

void hcs08Instruction::setAddressIX2()
{
   operandAddress = CPURegisters->H * 0x100 + CPURegisters->X + memory[CPURegisters->PC + 1 + extendedBytes] * 0x100 + memory[CPURegisters->PC + 2 + extendedBytes];
   //printf("set operand address IX2\n");
}

void hcs08Instruction::setAddressSP1()
{
   operandAddress = CPURegisters->SP + memory[CPURegisters->PC + 1 + extendedBytes];
   //printf("set operand address SP1\n");
}

void hcs08Instruction::setAddressSP2()
{
   operandAddress = CPURegisters->SP + memory[CPURegisters->PC + 1 + extendedBytes] * 0x100 + memory[CPURegisters->PC + 2 + extendedBytes];
   //printf("set operand address SP2\n");
}

// ------------------------------------
//
//    Disassemble functions
//
// ------------------------------------

void hcs08Instruction::disassembleTextINH(char *DisassembleText)
{
   sprintf(DisassembleText,"%s",MnemonicString);
}

void hcs08Instruction::disassembleTextIMM8(char *DisassembleText)
{
   sprintf(DisassembleText,"%s #%02X",MnemonicString, memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextIMM16(char *DisassembleText)
{
   sprintf(DisassembleText,"%s #%04X",MnemonicString, memory[CPURegisters->PC + 1] * 0x100 + memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextDIR(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X",MnemonicString, memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextDIRREL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X %04X",MnemonicString, memory[CPURegisters->PC + 1], CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextREL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X",MnemonicString,CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextEXT(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %04X",MnemonicString, memory[CPURegisters->PC + 1] * 0x100 + memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextIX0(char *DisassembleText)
{
   sprintf(DisassembleText,"%s ,X",MnemonicString);
}

void hcs08Instruction::disassembleTextIXP(char *DisassembleText)
{
   sprintf(DisassembleText,"%s X+",MnemonicString);
}

void hcs08Instruction::disassembleTextIX1(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X,X",MnemonicString,memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextI1P(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X,X+",MnemonicString,memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextIX2(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %04X,X",MnemonicString, memory[CPURegisters->PC + 1] * 0x100 + memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextSP1(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X,SP",MnemonicString,memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextSP2(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %04X,SP",MnemonicString, memory[CPURegisters->PC + 1] * 0x100 + memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextDIRDIR(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X,%02X",MnemonicString, memory[CPURegisters->PC + 1], memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextDIRIXP(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X,X+",MnemonicString, memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextIMMDIR(char *DisassembleText)
{
   sprintf(DisassembleText,"%s #%02X,%02X",MnemonicString, memory[CPURegisters->PC + 1], memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextIXPDIR(char *DisassembleText)
{
   sprintf(DisassembleText,"%s ,X+,%02X",MnemonicString, memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextIMMREL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s #%02X,%04X",MnemonicString, memory[CPURegisters->PC + 1],CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextI1PREL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X,X+,%04X",MnemonicString, memory[CPURegisters->PC + 1],CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextIXPREL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s ,X+,%04X",MnemonicString, CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextSP1REL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X,SP,%04X",MnemonicString, memory[CPURegisters->PC + 1],CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 2]);
}

void hcs08Instruction::disassembleTextINHREL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %04X",MnemonicString, CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextIX0REL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s ,X,%04X",MnemonicString, CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 1]);
}

void hcs08Instruction::disassembleTextIX1REL(char *DisassembleText)
{
   sprintf(DisassembleText,"%s %02X,X,%02X",MnemonicString, memory[CPURegisters->PC + 1],CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 2]);
}

// ------------------------------------
//
//    Mnemonic operations
//
// ------------------------------------


// ------------------------------------
// Table 6-1. Load and Store Instructions
//
void hcs08Instruction::mnemonicOperationLDA  ()
{
   //printf("LDA operation, operandAddress:%X, value %X, HX: %X\n",operandAddress, memory[operandAddress],CPURegisters->H * 0x100 + CPURegisters->X);
   TempResult8bit = CPURegisters->A = memory[operandAddress];
}

void hcs08Instruction::mnemonicOperationLDHX ()
{
   CPURegisters->H = memory[operandAddress];
   CPURegisters->X = memory[operandAddress + 1];
   TempResult16bit = CPURegisters->H * 0x100 + CPURegisters->X;
   //printf("LDHX operation, operandAddress:%X, value %X, HX: %X\n",operandAddress, memory[operandAddress],TempResult16bit);
}

void hcs08Instruction::mnemonicOperationLDX  ()
{
   //printf("LDX operation, operandAddress:%X, value %X, HX: %X\n",operandAddress, memory[operandAddress],CPURegisters->H * 0x100 + CPURegisters->X);
   TempResult8bit = CPURegisters->X = memory[operandAddress];
}

void hcs08Instruction::mnemonicOperationSTA  ()
{
   //printf("STA operation, operandAddress:%X, value %X, HX: %X\n",operandAddress, memory[operandAddress],CPURegisters->H * 0x100 + CPURegisters->X);
   TempResult8bit = memory[operandAddress] = CPURegisters->A;
}

void hcs08Instruction::mnemonicOperationSTHX ()
{
   memory[operandAddress]     = CPURegisters->H;
   memory[operandAddress + 1] = CPURegisters->X;
   TempResult16bit = CPURegisters->H * 256 + CPURegisters->X;
   //printf("STHX operation, operandAddress:%X, value %X, HX: %X\n",operandAddress, memory[operandAddress]*0x100+memory[operandAddress+1],TempResult16bit);
}

void hcs08Instruction::mnemonicOperationSTX  ()
{
   //printf("STX operation, operandAddress:%X, value %X, HX: %X\n",operandAddress, memory[operandAddress],CPURegisters->H * 0x100 + CPURegisters->X);
   TempResult8bit = memory[operandAddress] = CPURegisters->X;
}


// ------------------------------------------------------------------------
// Table 6-2. BSET, BCLR, Move, and Transfer Instructions
//
void hcs08Instruction::mnemonicOperationBSET ()
{
   // Set Bit n in Memory (Mn <- 1)
   char bitNo = (opCode - 0x10) / 2;
   memory[operandAddress] |= (0x01 << bitNo);
   //printf("BSET operation, operandAddress:%X, value %X, bit number: %X\n",operandAddress, memory[operandAddress],bitNo);
}

void hcs08Instruction::mnemonicOperationBCLR ()
{
   // Clear Bit n in Memory (Mn <- 0)
   char bitNo = (opCode - 0x11) / 2;
   memory[operandAddress] &= ~((unsigned char)(0x01 << bitNo));
   //printf("BCLR operation, operandAddress:%X, value %X, bit number: %X\n",operandAddress, memory[operandAddress],bitNo);
}

void hcs08Instruction::mnemonicOperationMOV  ()
{
   unsigned short operandAddressFrom = operandAddress;

   if(opCode == 0x4E || opCode == 0x6E) CPURegisters->PC++;

   if(opCode == 0x4E) setAddressDIR();
   else if(opCode == 0x5E) setAddressIXP();
   else if(opCode == 0x6E) setAddressDIR();
   else if(opCode == 0x7E) setAddressDIR();

   if(opCode == 0x4E || opCode == 0x6E) CPURegisters->PC--;

   TempResult8bit = memory[operandAddress] = memory[operandAddressFrom];

   //printf("MOV operation, operandAddressFrom:%X, operandAddressTo:%X, value %X\n",operandAddressFrom, operandAddress, memory[operandAddress]);
}

void hcs08Instruction::mnemonicOperationTAX  ()
{
   CPURegisters->X = CPURegisters->A;
   //printf("TAX operation, X:%X, A:%X\n",CPURegisters->X,CPURegisters->A);
}

void hcs08Instruction::mnemonicOperationTXA  ()
{
   CPURegisters->A = CPURegisters->X;
   //printf("TXA operation, A:%X, X:%X\n",CPURegisters->A,CPURegisters->X);
}

void hcs08Instruction::mnemonicOperationTAP  ()
{
   CPURegisters->setCCR(CPURegisters->A);
   //printf("TAP transfer A to CCR, A:%X, X:%X\n",CPURegisters->A,CPURegisters->getCCR());
}

void hcs08Instruction::mnemonicOperationTPA  ()
{
   CPURegisters->A = CPURegisters->getCCR();
   //printf("TPA transfer CCR to A, A:%X, X:%X\n",CPURegisters->A,CPURegisters->getCCR());
}

void hcs08Instruction::mnemonicOperationNSA  ()
{
   CPURegisters->A = ((CPURegisters->A >> 4) & 0x0F) + ((CPURegisters->A << 4) & 0xF0);
   //printf("NSA - Nibble Swap Accumulator, A:%X\n",CPURegisters->A);
}

// ------------------------------------------------------------------------
// Table 6-3. Add, Subtract, Multiply, and Divide Instructions
//
void hcs08Instruction::mnemonicOperationADC  ()
{
   TempBeforeOperation8bit = CPURegisters->A;
   TempMemory8bit = memory[operandAddress];
   TempResult8bit = CPURegisters->A = CPURegisters->A + TempMemory8bit + CPURegisters->STATUS_C;
}

void hcs08Instruction::mnemonicOperationADD  ()
{
   TempBeforeOperation8bit = CPURegisters->A;
   TempMemory8bit = memory[operandAddress];
   TempResult8bit = CPURegisters->A = CPURegisters->A + TempMemory8bit;
}

void hcs08Instruction::mnemonicOperationAIS  ()
{
   //printf("Stack Pointer before operation:, SP:%X\n",CPURegisters->SP);
   CPURegisters->SP += (signed char)memory[operandAddress];
   //printf("Add Immediate Value (Signed) to Stack Pointer, SP:%X, imm: %i\n",CPURegisters->SP,(signed char)memory[operandAddress]);
}

void hcs08Instruction::mnemonicOperationAIX  ()
{
   unsigned short HX = CPURegisters->getIndexReg();
   //printf("Index before operation:, HX:%X\n",HX);
   HX += (signed char)memory[operandAddress];
   //printf("Add Immediate Value (Signed) to index register, HX:%X, imm: %i\n",HX,(signed char)memory[operandAddress]);
   CPURegisters->setIndexReg(HX);
}

void hcs08Instruction::mnemonicOperationSUB  ()
{
   TempBeforeOperation8bit = CPURegisters->A;
   TempMemory8bit = memory[operandAddress];
   TempResult8bit = CPURegisters->A = CPURegisters->A - TempMemory8bit;
}

void hcs08Instruction::mnemonicOperationSBC  ()
{
   TempBeforeOperation8bit = CPURegisters->A;
   TempMemory8bit = memory[operandAddress];
   TempResult8bit = CPURegisters->A = CPURegisters->A - TempMemory8bit - CPURegisters->STATUS_C;
}

void hcs08Instruction::mnemonicOperationMUL  ()
{
   TempResult16bit = CPURegisters->X * CPURegisters->A;
   CPURegisters->X = (TempResult16bit & 0xFF00) >> 8;
   CPURegisters->A = TempResult16bit & 0x00FF;
   CPURegisters->STATUS_H = 0;
   CPURegisters->STATUS_C = 0;
   //printf("MUL, X:%X, A: %X\n",CPURegisters->X,CPURegisters->A);

}

void hcs08Instruction::mnemonicOperationDIV  ()
{
   unsigned short TempHA = CPURegisters->H * 256 + CPURegisters->A;
   if(CPURegisters->X > 0)
   {
      TempResult16bit = TempHA / CPURegisters->X;
      if(TempResult16bit < 0x100){
         CPURegisters->A = TempResult16bit & 0x00FF;  // Quotient
         (CPURegisters->A > 0) ? CPURegisters->H = TempHA % CPURegisters->X : CPURegisters->H = 0;  // Remainder
         CPURegisters->STATUS_C = 0;
      }
      else
         CPURegisters->STATUS_C = 1;
   }
   else
      CPURegisters->STATUS_C = 1;

   CPURegisters->STATUS_Z = (TempResult16bit == 0) ? 1 : 0;

   //printf("DIV, Dividend HA: %X, divisor:%X, Quotient: %X, remainder: %X\n",TempHA,CPURegisters->X,CPURegisters->A,CPURegisters->H);
   //printf("Flags, C:%d, Z: %d\n",CPURegisters->STATUS_C,CPURegisters->STATUS_Z);
}


// ------------------------------------------------------------------------
// Table 6-4. Other Arithmetic Instructions
//    - Increment, Decrement, Clear, and Negate
//

void hcs08Instruction::mnemonicOperationINC  ()
{
   switch(memory[CPURegisters->PC])
   {
      case 0x4C:  // INCA
         TempBeforeOperation8bit = CPURegisters->A;
         TempResult8bit = CPURegisters->A += 1;
         break;
      case 0x5C:  // INCX
         TempBeforeOperation8bit = CPURegisters->X;
         TempResult8bit = CPURegisters->X += 1;
         break;
      default: // Memory
         TempBeforeOperation8bit = memory[operandAddress];
         TempResult8bit = memory[operandAddress] += 1;
         break;
   }
}

void hcs08Instruction::mnemonicOperationDEC  ()
{
   switch(memory[CPURegisters->PC])
   {
      case 0x4A:  // DECA
         TempBeforeOperation8bit = CPURegisters->A;
         TempResult8bit = CPURegisters->A -= 1;
         break;
      case 0x5A:  // DECX
         TempBeforeOperation8bit = CPURegisters->X;
         TempResult8bit = CPURegisters->X -= 1;
         break;
      default: // Memory
         TempBeforeOperation8bit = memory[operandAddress];
         TempResult8bit = memory[operandAddress] -= 1;
         break;
   }
}

void hcs08Instruction::mnemonicOperationCLR  ()
{
   switch(memory[CPURegisters->PC]) {
      case 0x4F: CPURegisters->A = 0x00; break; // CLR A
      case 0x5F: CPURegisters->X = 0x00; break; // CLR X
      case 0x8C: CPURegisters->H = 0x00; break; // CLR H
      default: memory[operandAddress] = 0x00; break; // CLR Memory
   }
   CPURegisters->STATUS_V = 0;
   CPURegisters->STATUS_N = 0;
   CPURegisters->STATUS_Z = 1;
   //printf("A: %X, X: %X, H: %X, V: %i, N: %i, Z: %i, mem[190B]: %X\n",CPURegisters->A,CPURegisters->X,CPURegisters->H,CPURegisters->STATUS_V,CPURegisters->STATUS_N, CPURegisters->STATUS_Z,memory[0x190B]);
}

void hcs08Instruction::mnemonicOperationNEG  ()
{
   switch(memory[CPURegisters->PC]) {
      case 0x40:
         //TempBeforeOperation8bit = CPURegisters->A;
         TempResult8bit = CPURegisters->A = (~CPURegisters->A) + 1; break; // NEG A
      case 0x50:
         //TempBeforeOperation8bit = CPURegisters->X;
         TempResult8bit = CPURegisters->X = (~CPURegisters->X) + 1; break; // NEG X
      default:
         //TempBeforeOperation8bit = memory[operandAddress;
         TempResult8bit = memory[operandAddress] = (~memory[operandAddress]) + 1; break; // NEG memory
   }
   CPURegisters->STATUS_V = (TempResult8bit == 0x80) ? 1 : 0;
   CPURegisters->STATUS_N = (TempResult8bit & 0x80) >> 7;
   CPURegisters->STATUS_Z = (TempResult8bit == 0x00) ? 1 : 0;
   CPURegisters->STATUS_C = (TempResult8bit != 0x00) ? 1 : 0;
   //printf("A: %X, X: %X, V: %i, N: %i, Z: %i, C: %i, Result: %X\n",CPURegisters->A,CPURegisters->X,CPURegisters->STATUS_V,CPURegisters->STATUS_N, CPURegisters->STATUS_Z,CPURegisters->STATUS_C,memory[operandAddress] /*TempResult8bit*/ );
}

void hcs08Instruction::mnemonicOperationCMP  ()
{
   TempBeforeOperation8bit = CPURegisters->A;
   TempMemory8bit = memory[operandAddress];
   TempResult8bit = CPURegisters->A - TempMemory8bit;
   //printf("TempMemory8bit: %X, TempResult8bit: %X, A: %X\n",TempMemory8bit,TempResult8bit,CPURegisters->A);
}

void hcs08Instruction::mnemonicOperationCPHX ()
{
   TempBeforeOperation16bit = CPURegisters->H * 0x100 + CPURegisters->X;
   TempMemory16bit = memory[operandAddress] * 0x100 + memory[operandAddress + 1];
   TempResult16bit = TempBeforeOperation16bit - TempMemory16bit;
   //printf("TempBeforeOperation16bit: %X, TempMemory16bit: %X, TempResult16bit: %X\n",TempBeforeOperation16bit,TempMemory16bit,TempResult16bit);
}

void hcs08Instruction::mnemonicOperationCPX  ()
{
   TempBeforeOperation8bit = CPURegisters->X;
   TempMemory8bit = memory[operandAddress];
   TempResult8bit = CPURegisters->X - TempMemory8bit;
   //printf("TempBeforeOperation8bit: %X, TempMemory8bit: %X, TempResult8bit: %X\n",TempBeforeOperation8bit,TempMemory8bit,TempResult8bit);
}

void hcs08Instruction::mnemonicOperationTST  ()
{
   switch(memory[CPURegisters->PC])
   {
      case 0x4D: TempResult8bit = CPURegisters->A; break; // TSTA
      case 0x5D: TempResult8bit = CPURegisters->X; break; // TSTX
      default:   TempResult8bit = memory[operandAddress]; break; // Memory
   }
}

void hcs08Instruction::mnemonicOperationDAA  ()
{
   unsigned char FirstDigit = (CPURegisters->A & 0x0F) + CPURegisters->STATUS_C;
   unsigned char SecondDigit = 0;
   unsigned char BCD_half_carry = 0;
   unsigned char Correction_factor = 0x00;

   //Set adjustment for first digit
   if((FirstDigit >= 0xA && CPURegisters->STATUS_H == 0) || CPURegisters->STATUS_H == 1)
      Correction_factor = 0x06;

   //Set half carry bit for first digit
   if(FirstDigit >= 0xA && CPURegisters->STATUS_H == 0)
      BCD_half_carry = 1;

   SecondDigit = ((CPURegisters->A & 0xF0) >> 4) + BCD_half_carry;

   //printf("SecondDigit: %X, C flag: %X\n",SecondDigit,CPURegisters->STATUS_C);

   //Set adjustment and carry bit for second digit
   if((SecondDigit >= 0xA && CPURegisters->STATUS_C == 0) || CPURegisters->STATUS_C == 1)  {
      Correction_factor += 0x60;
      CPURegisters->STATUS_C = 1;
   }

   TempResult8bit = CPURegisters->A += Correction_factor;
   //printf("TempResult8bit: %X, C: %i\n",TempResult8bit,CPURegisters->STATUS_C);
}

// ------------------------------------------------------------------------
// Table 6-5. Logical Operation Instructions
//

void hcs08Instruction::mnemonicOperationAND  ()
{
   TempResult8bit = CPURegisters->A &= memory[operandAddress];
}

void hcs08Instruction::mnemonicOperationORA  ()
{
   TempResult8bit = CPURegisters->A |= memory[operandAddress];
}

void hcs08Instruction::mnemonicOperationEOR  ()
{
   TempResult8bit = CPURegisters->A ^= memory[operandAddress];
}

void hcs08Instruction::mnemonicOperationCOM  ()
{
   switch(memory[CPURegisters->PC])
   {
      case 0x43: TempResult8bit = CPURegisters->A = ~CPURegisters->A; break; // COMA
      case 0x53: TempResult8bit = CPURegisters->X = ~CPURegisters->X; break; // COMX
      default:   TempResult8bit = memory[operandAddress] = ~memory[operandAddress]; break; // Memory
   }
   CPURegisters->STATUS_C = 1;
}

void hcs08Instruction::mnemonicOperationBIT  ()
{
   TempResult8bit = CPURegisters->A & memory[operandAddress];
}

// ------------------------------------------------------------------------
// Table 6-6. Shift and Rotate Instructions
//

void hcs08Instruction::mnemonicOperationLSL  ()
{
   unsigned char *Value8bit = nullptr;
   switch(memory[CPURegisters->PC])
   {
      case 0x48: Value8bit = &CPURegisters->A; break; // LSLA
      case 0x58: Value8bit = &CPURegisters->X; break; // LSLX
      default:   Value8bit = &memory[operandAddress]; break; // LSL Memory
   }
   CPURegisters->STATUS_C = (*Value8bit >> 7) & 0x01;
   *Value8bit = (*Value8bit << 1);
   CPURegisters->STATUS_V = CPURegisters->STATUS_C ^ ((*Value8bit >> 7) & 0x01);
   TempResult8bit = *Value8bit;
}

void hcs08Instruction::mnemonicOperationLSR  ()
{
   unsigned char *Value8bit = nullptr;
   switch(memory[CPURegisters->PC])
   {
      case 0x44: Value8bit = &CPURegisters->A; break; // LSRA
      case 0x54: Value8bit = &CPURegisters->X; break; // LSRX
      default:   Value8bit = &memory[operandAddress]; break; // LSR Memory
   }
   CPURegisters->STATUS_C = *Value8bit & 0x01;
   *Value8bit = (*Value8bit >> 1);
   CPURegisters->STATUS_V = CPURegisters->STATUS_C ^ ((*Value8bit >> 7) & 0x01);
   TempResult8bit = *Value8bit;
}

void hcs08Instruction::mnemonicOperationASR  ()
{
   unsigned char *Value8bit = nullptr;
   switch(memory[CPURegisters->PC])
   {
      case 0x47: Value8bit = &CPURegisters->A; break; // ASRA
      case 0x57: Value8bit = &CPURegisters->X; break; // ASRX
      default:   Value8bit = &memory[operandAddress]; break; // ASR Memory
   }
   CPURegisters->STATUS_C = *Value8bit & 0x01;
   unsigned char Temp8bit = *Value8bit & 0x80;
   *Value8bit = (*Value8bit >> 1) + Temp8bit;
   CPURegisters->STATUS_V = CPURegisters->STATUS_C ^ ((*Value8bit >> 7) & 0x01);
   TempResult8bit = *Value8bit;
}

void hcs08Instruction::mnemonicOperationROL  ()
{
   unsigned char *Value8bit = nullptr;
   switch(memory[CPURegisters->PC])
   {
      case 0x49: Value8bit = &CPURegisters->A; break; // ROLA
      case 0x59: Value8bit = &CPURegisters->X; break; // ROLX
      default:   Value8bit = &memory[operandAddress]; break; // ROL Memory
   }
   unsigned char Temp_STATUS_C = CPURegisters->STATUS_C;
   CPURegisters->STATUS_C = (*Value8bit >> 7) & 0x01;
   *Value8bit = (*Value8bit << 1) + Temp_STATUS_C;
   CPURegisters->STATUS_V = CPURegisters->STATUS_C ^ ((*Value8bit >> 7) & 0x01);
   TempResult8bit = *Value8bit;
}

void hcs08Instruction::mnemonicOperationROR  ()
{
   unsigned char *Value8bit = nullptr;
   switch(memory[CPURegisters->PC])
   {
      case 0x46: Value8bit = &CPURegisters->A; break; // RORA
      case 0x56: Value8bit = &CPURegisters->X; break; // RORX
      default:   Value8bit = &memory[operandAddress]; break; // ROR Memory
   }
   unsigned char Temp_STATUS_C = CPURegisters->STATUS_C;
   CPURegisters->STATUS_C = *Value8bit & 0x01;
   *Value8bit = (*Value8bit >> 1) + (Temp_STATUS_C << 7);
   CPURegisters->STATUS_V = CPURegisters->STATUS_C ^ ((*Value8bit >> 7) & 0x01);
   TempResult8bit = *Value8bit;
}

// ------------------------------------------------------------------------
// Table 6-7. Jump and Branch Instructions
//

void hcs08Instruction::mnemonicOperationJMP  ()
{
   AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBRA  ()
{
   AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBRN  ()
{
   //Never branch (NOP)
}

void hcs08Instruction::mnemonicOperationBEQ  ()
{
   if(CPURegisters->STATUS_Z == 1) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBNE  ()
{
   if(CPURegisters->STATUS_Z == 0) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBCC  ()
{
   if(CPURegisters->STATUS_C == 0) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBCS  ()
{
   if(CPURegisters->STATUS_C == 1) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBPL  ()
{
   if(CPURegisters->STATUS_N == 0) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBMI  ()
{
   if(CPURegisters->STATUS_N == 1) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBIL  ()
{
   //printf("Instruction BIL is not implemented yet!\n");
}

void hcs08Instruction::mnemonicOperationBIH  ()
{
   //printf("Instruction BIH is not implemented yet!\n");
}

void hcs08Instruction::mnemonicOperationBMC  ()
{
   if(CPURegisters->STATUS_I == 0) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBMS  ()
{
   if(CPURegisters->STATUS_I == 1) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBHCC ()
{
   if(CPURegisters->STATUS_H == 0) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBHCS ()
{
   if(CPURegisters->STATUS_H == 1) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBLT  ()
{
   if((CPURegisters->STATUS_N ^ CPURegisters->STATUS_V) == 1) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBLE  ()
{
   if((CPURegisters->STATUS_Z || (CPURegisters->STATUS_N ^ CPURegisters->STATUS_V)) == 1) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBGE  ()
{
   if((CPURegisters->STATUS_N ^ CPURegisters->STATUS_V) == 0) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBGT  ()
{
   if((CPURegisters->STATUS_Z || (CPURegisters->STATUS_N ^ CPURegisters->STATUS_V)) == 0) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBLS  ()
{
   if((CPURegisters->STATUS_C || CPURegisters->STATUS_Z) == 1) AlteredNextAddress = operandAddress;
}

void hcs08Instruction::mnemonicOperationBHI  ()
{
   if((CPURegisters->STATUS_C || CPURegisters->STATUS_Z) == 0) AlteredNextAddress = operandAddress;
}

// ------------------------------------------------------------------------
// Table 6-9. Bit Branches and Loop Conrol
//

void hcs08Instruction::mnemonicOperationBRCLR()
{
   char bitNo = (opCode - 0x1) / 2;
   if((memory[operandAddress] & (0x01 << bitNo)) == 0) {
      CPURegisters->STATUS_C = 1;
      AlteredNextAddress = CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 2];
   }
   else
      CPURegisters->STATUS_C = 0;
}

void hcs08Instruction::mnemonicOperationBRSET()
{
   char bitNo = (opCode - 0x0) / 2;
   if((memory[operandAddress] & (0x01 << bitNo)) > 0) {
      CPURegisters->STATUS_C = 1;
      AlteredNextAddress = CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + 2];
   }
   else
      CPURegisters->STATUS_C = 0;
}

void hcs08Instruction::mnemonicOperationCBEQ ()
{
   unsigned char *Value8bit = nullptr;
   if(memory[CPURegisters->PC] == 0x51)
      Value8bit = &CPURegisters->X;
   else
      Value8bit = &CPURegisters->A;

   if(*Value8bit == memory[operandAddress])
   {
      //printf("Relativ address: %i\n",(char)memory[CPURegisters->PC + noOfBytes - 1]);
      AlteredNextAddress = CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + noOfBytes - 1];
   }
}

void hcs08Instruction::mnemonicOperationDBNZ ()
{
   unsigned char *Value8bit = nullptr;
   switch(memory[CPURegisters->PC])
   {
      case 0x4B: Value8bit = &CPURegisters->A; break; // DBNZA
      case 0x5B: Value8bit = &CPURegisters->X; break; // DBNZX
      default:   Value8bit = &memory[operandAddress]; break; // DBNZ Memory
   }
   *Value8bit = *Value8bit - 1;

   if(*Value8bit != 0)
      AlteredNextAddress = CPURegisters->PC + noOfBytes + (char)memory[CPURegisters->PC + noOfBytes - 1];
}

// ------------------------------------------------------------------------
// Table 6-10. Stack-Related Instructions
//

void hcs08Instruction::mnemonicOperationRSP  ()
{
   CPURegisters->SP |= 0x00FF;
   //printf("SP: %X\n",CPURegisters->SP);
}

void hcs08Instruction::mnemonicOperationTXS  ()
{
   CPURegisters->SP = (CPURegisters->H * 0x100 + CPURegisters->X) - 1;
   //printf("SP: %X\n",CPURegisters->SP);
}

void hcs08Instruction::mnemonicOperationTSX  ()
{
   unsigned short HX = CPURegisters->SP + 1;
   CPURegisters->H = (HX & 0xFF00) >> 8;
   CPURegisters->X = HX & 0x00FF;
   //printf("HX: %X\n",CPURegisters->H * 0x100 + CPURegisters->X);
}

void hcs08Instruction::mnemonicOperationJSR  ()
{
   unsigned short PC = CPURegisters->PC + noOfBytes;
   memory[CPURegisters->SP--] = PC & 0x00FF;
   memory[CPURegisters->SP--] = (PC & 0xFF00) >> 8;
   AlteredNextAddress = operandAddress;
   //unsigned short SP = CPURegisters->SP;
   //printf("SP: %X, SP+1: %X, SP+2: %X,PC: %X\n",SP,memory[SP+1],memory[SP+2],CPURegisters->PC);
}

void hcs08Instruction::mnemonicOperationBSR  ()
{
   unsigned short NextInstrAddr = CPURegisters->PC + noOfBytes;
   memory[CPURegisters->SP--] = NextInstrAddr & 0x00FF;
   memory[CPURegisters->SP--] = (NextInstrAddr & 0xFF00) >> 8;
   AlteredNextAddress = NextInstrAddr + (char)memory[CPURegisters->PC + noOfBytes - 1];

   //unsigned short SP = CPURegisters->SP;
   //printf("SP: %X, SP+1: %X, SP+2: %X,PC: %X\n",SP,memory[SP+1],memory[SP+2],CPURegisters->PC);
}

void hcs08Instruction::mnemonicOperationRTS  ()
{
   //unsigned short SP = CPURegisters->SP;
   //printf("SP+1: %X, SP: %X, SP+2: %X,PC: %X\n",SP,memory[SP+1],memory[SP+2],CPURegisters->PC);

   AlteredNextAddress = memory[CPURegisters->SP + 1] * 0x100 + memory[CPURegisters->SP + 2];
   CPURegisters->SP += 2;

   //printf("New PC: %X\n",CPURegisters->PC);
}

void hcs08Instruction::mnemonicOperationSWI  ()
{
   unsigned short PC = CPURegisters->PC + noOfBytes;
   memory[CPURegisters->SP--] = PC & 0x00FF;
   memory[CPURegisters->SP--] = (PC & 0xFF00) >> 8;
   memory[CPURegisters->SP--] = CPURegisters->X;
   memory[CPURegisters->SP--] = CPURegisters->A;
   memory[CPURegisters->SP--] = CPURegisters->getCCR();
   CPURegisters->STATUS_I = 1;
   AlteredNextAddress = memory[0xFFFC] * 0x100 + memory[0xFFFD];

   //unsigned short SP = CPURegisters->SP;
   //printf("SP: %X, SP+1(CCR): %X, SP+2(A): %X, SP+3(X): %X, SP+4(PCH): %X, SP+5(PCL): %X,PC: %X\n"
   //   ,SP,memory[SP+1],memory[SP+2],memory[SP+3],memory[SP+4],memory[SP+5],CPURegisters->PC);
}

void hcs08Instruction::mnemonicOperationRTI  ()
{
   CPURegisters->setCCR(memory[(++CPURegisters->SP)]);
   CPURegisters->A = memory[(++CPURegisters->SP)];
   CPURegisters->X = memory[(++CPURegisters->SP)];
   AlteredNextAddress = memory[CPURegisters->SP + 1] * 0x100 + memory[CPURegisters->SP + 2];
   CPURegisters->SP += 2;
   /*unsigned short SP = CPURegisters->SP;
   printf("SP: %X, SP-4(CCR): %X, SP-3(A): %X, SP-2(X): %X, SP-1(PCH): %X, SP-0(PCL): %X,PC: %X\n"
      ,SP,memory[SP-4],memory[SP-3],memory[SP-2],memory[SP-1],memory[SP-0],CPURegisters->PC);
   printf("X: %X, A: %X, CCR: %X\n",CPURegisters->X,CPURegisters->A,CPURegisters->getCCR());*/
}

void hcs08Instruction::mnemonicOperationPSH  ()
{
   unsigned char *Value8bit = nullptr;
   switch(memory[CPURegisters->PC])
   {
      case 0x87: Value8bit = &CPURegisters->A; break; // PSHA
      case 0x8B: Value8bit = &CPURegisters->H; break; // PSHH
      case 0x89: Value8bit = &CPURegisters->X; break; // PSHX
   }
   //printf("*Value8bit: %X\n",*Value8bit);
   memory[CPURegisters->SP--] = *Value8bit;

   /*unsigned short SP = CPURegisters->SP;
   printf("SP: %X, SP+1: %X\n",SP,memory[SP+1]);
   printf("X: %X, A: %X, H: %X\n",CPURegisters->X,CPURegisters->A,CPURegisters->H);*/
}

void hcs08Instruction::mnemonicOperationPUL  ()
{
   unsigned char *Value8bit = nullptr;
   switch(memory[CPURegisters->PC])
   {
      case 0x86: Value8bit = &CPURegisters->A; break; // PULA
      case 0x8A: Value8bit = &CPURegisters->H; break; // PULH
      case 0x88: Value8bit = &CPURegisters->X; break; // PULX
   }
   *Value8bit = memory[(++CPURegisters->SP)];
   /*unsigned short SP = CPURegisters->SP;
   printf("SP: %X, SP+0: %X\n",SP,memory[SP+0]);
   printf("X: %X, A: %X, H: %X\n",CPURegisters->X,CPURegisters->A,CPURegisters->H);*/
   //printf("*Value8bit: %X\n",*Value8bit);
}

// ------------------------------------------------------------------------
// Table 6-11. Miscellaneous Instructions
//

void hcs08Instruction::mnemonicOperationNOP  ()
{
}

void hcs08Instruction::mnemonicOperationSEC  ()
{
   CPURegisters->STATUS_C = 1;
   //printf("STATUS_C: %X\n",CPURegisters->STATUS_C);
}

void hcs08Instruction::mnemonicOperationCLC  ()
{
   CPURegisters->STATUS_C = 0;
   //printf("STATUS_C: %X\n",CPURegisters->STATUS_C);
}

void hcs08Instruction::mnemonicOperationSEI  ()
{
   CPURegisters->STATUS_I = 1;
   //printf("STATUS_I: %X\n",CPURegisters->STATUS_I);
}

void hcs08Instruction::mnemonicOperationCLI  ()
{
   CPURegisters->STATUS_I = 0;
   //printf("STATUS_I: %X\n",CPURegisters->STATUS_I);
}

void hcs08Instruction::mnemonicOperationBGND ()
{
   printf("Instruction BGND is not implemented yet!\n");
}

void hcs08Instruction::mnemonicOperationWAIT ()
{
   printf("Instruction WAIT is not implemented yet!\n");
}

void hcs08Instruction::mnemonicOperationSTOP ()
{
   printf("Instruction STOP is not implemented yet!\n");
}

void hcs08Instruction::mnemonicOperationPAGE2()
{
   printf("Instruction PAGE2, illegal Instruction!\n");
}

void hcs08Instruction::mnemonicOperationNA   ()
{
   printf("Illegal Instruction, opcode: %X\n",memory[CPURegisters->PC]);
}

// ------------------------------------
//
//    Set flags functions
//
// ------------------------------------

void hcs08Instruction::setFlagMethodNZ8B()
{
   //printf("Set flags NZ 8 bit\n");
   CPURegisters->STATUS_N = (TempResult8bit >> 7) & 0x01;
   CPURegisters->STATUS_Z = (TempResult8bit == 0) ? 1 : 0;
   //printf("Result: 0x%X, A: %X, X: %X, V: %i, N: %i, Z: %i, C: %i\n",TempResult8bit, CPURegisters->A, CPURegisters->X, CPURegisters->STATUS_V,CPURegisters->STATUS_N,CPURegisters->STATUS_Z,CPURegisters->STATUS_C);
}

void hcs08Instruction::setFlagMethodVNZ8B()
{
   //printf("Set flags VNZ 8 bit\n");
   CPURegisters->STATUS_V = 0;
   CPURegisters->STATUS_N = (TempResult8bit >> 7) & 0x01;
   CPURegisters->STATUS_Z = (TempResult8bit == 0) ? 1 : 0;
   //printf("Result: 0x%X, V: %i, N: %i, Z: %i\n",TempResult8bit, CPURegisters->STATUS_V,CPURegisters->STATUS_N,CPURegisters->STATUS_Z);
}

void hcs08Instruction::setFlagMethodVNZ16B()
{
   //printf("Set flags VNZ 16 bit\n");
   CPURegisters->STATUS_V = 0;
   CPURegisters->STATUS_N = (TempResult16bit >> 15) & 0x01;
   CPURegisters->STATUS_Z = (TempResult16bit == 0) ? 1 : 0;
   //printf("Result: 0x%X, V: %i, N: %i, Z: %i\n",TempResult16bit, CPURegisters->STATUS_V,CPURegisters->STATUS_N,CPURegisters->STATUS_Z);
}

void hcs08Instruction::setFlagMethodVHNZC_ADD_8B()
{
   unsigned char A7,A3,M7,M3,R7,R3;
   //printf("Set flags V, H, N, Z, C for ADD/ADC 8 bit\n");
   A7 = (TempBeforeOperation8bit & 0x80) >> 7; M7 = (TempMemory8bit & 0x80) >> 7; R7 = (TempResult8bit & 0x80) >> 7;
   A3 = (TempBeforeOperation8bit & 0x08) >> 3; M3 = (TempMemory8bit & 0x08) >> 3; R3 = (TempResult8bit & 0x08) >> 3;
   //printf("A7: %i, A3: %i, M7: %i, M3: %i, R7: %i, R3: %i\n",A7, A3, M7, M3, R7, R3);
   CPURegisters->STATUS_V = (A7 && M7 && !R7) || (!A7 && !M7 && R7);  // A7 & M7 & /R7 | /A7 & /M7 & R7 - flag - 2's complement overflow
   CPURegisters->STATUS_H = (A3 && M3) || (M3 && !R3) || (!R3 && A3);  // A3 & M3 | M3 & /R3 | /R3 & A3
   CPURegisters->STATUS_N = R7;
   CPURegisters->STATUS_Z = (TempResult8bit == 0) ? 1 : 0;
   CPURegisters->STATUS_C = (A7 && M7) || (M7 && !R7) || (A7 && !R7); // A7 & M7 | M7 & /R7 | A7 & /R7
   //printf("Result: 0x%X, V: %i, H: %i, N: %i, Z: %i, C: %i\n",TempResult8bit, CPURegisters->STATUS_V, CPURegisters->STATUS_H, CPURegisters->STATUS_N,CPURegisters->STATUS_Z, CPURegisters->STATUS_C);
}

void hcs08Instruction::setFlagMethodVHNZC_SUB_8B()
{
   unsigned char A7,M7,R7;
   //printf("Set flags V, H, N, Z, C for SUB/SBC 8 bit\n");
   A7 = (TempBeforeOperation8bit & 0x80) >> 7; M7 = (TempMemory8bit & 0x80) >> 7; R7 = (TempResult8bit & 0x80) >> 7;
   //printf("A7: %i, M7: %i, R7: %i\n",A7, M7, R7);
   CPURegisters->STATUS_V = (A7 && !M7 && !R7) || (!A7 && M7 && R7);  // A7 & /M7 & /R7 | /A7 & M7 & R7 - flag - 2's complement overflow
   CPURegisters->STATUS_N = R7;
   CPURegisters->STATUS_Z = (TempResult8bit == 0) ? 1 : 0;
   CPURegisters->STATUS_C = (!A7 && M7) || (M7 && R7) || (R7 && !A7); // /A7 & M7 | M7 & R7 | R7 & /A7
   //printf("Result: 0x%X, V: %i, N: %i, Z: %i, C: %i, A: %X\n",TempResult8bit, CPURegisters->STATUS_V, CPURegisters->STATUS_N,CPURegisters->STATUS_Z, CPURegisters->STATUS_C, CPURegisters->A);
}

void hcs08Instruction::setFlagMethodVNZ_INC_8B()
{
   unsigned char A7 = (TempBeforeOperation8bit & 0x80) >> 7;
   unsigned char R7 = (TempResult8bit & 0x80) >> 7;
   //printf("Set flags V, N, Z for INC 8 bit\n");
   //printf("A7: %i, R7: %i\n",A7, R7);
   CPURegisters->STATUS_V = (!A7 && R7);  // /A7 & /R7
   CPURegisters->STATUS_N = R7;
   CPURegisters->STATUS_Z = (TempResult8bit == 0) ? 1 : 0;
   //printf("Result: 0x%X, V: %i, N: %i, Z: %i, C: %i, A: %X, X: %X\n",TempResult8bit, CPURegisters->STATUS_V, CPURegisters->STATUS_N,CPURegisters->STATUS_Z, CPURegisters->STATUS_C,CPURegisters->A,CPURegisters->X);
}

void hcs08Instruction::setFlagMethodVNZ_DEC_8B()
{
   unsigned char A7 = (TempBeforeOperation8bit & 0x80) >> 7;
   unsigned char R7 = (TempResult8bit & 0x80) >> 7;
   //printf("Set flags V, N, Z for DEC 8 bit\n");
   //printf("A7: %i, R7: %i\n",A7, R7);
   CPURegisters->STATUS_V = (A7 && !R7);  // A7 & /R7
   CPURegisters->STATUS_N = R7;
   CPURegisters->STATUS_Z = (TempResult8bit == 0) ? 1 : 0;
   //printf("Result: 0x%X, V: %i, N: %i, Z: %i, C: %i, A: %X, X: %X\n",TempResult8bit, CPURegisters->STATUS_V, CPURegisters->STATUS_N,CPURegisters->STATUS_Z, CPURegisters->STATUS_C,CPURegisters->A,CPURegisters->X);
}

void hcs08Instruction::setFlagMethodVNZC_CPHX_16B()
{
   unsigned char H7 = (TempBeforeOperation16bit & 0x8000) >> 15;
   unsigned char M15 = (TempMemory16bit & 0x8000) >> 15;
   unsigned char R15 = (TempResult16bit & 0x8000) >> 15;
   //printf("Set flags V, H, N, Z, C for CPHX 16 bit\n");
   //printf("H7: %i, M15: %i, R15: %i\n",H7, M15, R15);
   CPURegisters->STATUS_V = (H7 && !M15 && !R15) || (!H7 && M15 && R15);  // H7 & /M15 & /R15 | /H7 & M15 & R15 - flag - 2's complement overflow
   CPURegisters->STATUS_N = R15;
   CPURegisters->STATUS_Z = (TempResult16bit == 0) ? 1 : 0;
   CPURegisters->STATUS_C = (!H7 && M15) || (M15 && R15) || (R15 && !H7); // /H7 & M15 | M15 & R15 | R15 & /A15
   //printf("V: %i, N: %i, Z: %i, C: %i\n", CPURegisters->STATUS_V, CPURegisters->STATUS_N,CPURegisters->STATUS_Z, CPURegisters->STATUS_C);
}
