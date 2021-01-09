#ifndef HCS08_INSTRUCTION_H
#define HCS08_INSTRUCTION_H

#include "hcs08_CPURegisters.h"

using namespace std;


class hcs08Instruction
{

   public:

      hcs08Instruction(unsigned char p_opCode, unsigned char *p_memory, char p_noOfBytes, char p_extendedBytes, char p_addressingMode, hcs08CPURegisters *p_CPURegisters, unsigned char p_InstMnemonic, unsigned char p_MnemonicFlagsMethod, const char *p_MnemonicString, unsigned char p_disassembleFunction);
      void getBytecodeText(char* str);
      void getAddressingModeAsText(char *str);

      char getInstructionLength();

      void Execute();
      void DisassembleText(char *disassemblyText);

      char noOfBytes = 0;

      char addressingMode = 0;
      char addressingModeAsText[20] = { 0 };

      char MnemonicString[8] = { 0 };



   private:

      unsigned char opCode;      //Opcode number

      hcs08CPURegisters *CPURegisters;

      unsigned char *memory;

      unsigned char InstMnemonic;

      //char addressingMode2nd = 0;

      void setAddressIMM();
      void setAddressDIR();
      void setAddressREL();
      void setAddressEXT();
      void setAddressIX0();
      void setAddressIXP();
      void setAddressIX1();
      void setAddressI1P();
      void setAddressIX2();
      void setAddressSP1();
      void setAddressSP2();

      // Disassemble function
      void disassembleTextINH(char *DisassembleText);
      void disassembleTextIMM8(char *DisassembleText);
      void disassembleTextIMM16(char *DisassembleText);
      void disassembleTextDIR(char *DisassembleText);
      void disassembleTextDIRREL(char *DisassembleText);
      void disassembleTextREL(char *DisassembleText);
      void disassembleTextEXT(char *DisassembleText);
      void disassembleTextIX0(char *DisassembleText);
      void disassembleTextIXP(char *DisassembleText);
      void disassembleTextIX1(char *DisassembleText);
      void disassembleTextI1P(char *DisassembleText);
      void disassembleTextIX2(char *DisassembleText);
      void disassembleTextSP1(char *DisassembleText);
      void disassembleTextSP2(char *DisassembleText);
      void disassembleTextDIRDIR(char *DisassembleText);
      void disassembleTextDIRIXP(char *DisassembleText);
      void disassembleTextIMMDIR(char *DisassembleText);
      void disassembleTextIXPDIR(char *DisassembleText);
      void disassembleTextIMMREL(char *DisassembleText);
      void disassembleTextI1PREL(char *DisassembleText);
      void disassembleTextIXPREL(char *DisassembleText);
      void disassembleTextSP1REL(char *DisassembleText);
      void disassembleTextINHREL(char *DisassembleText);
      void disassembleTextIX0REL(char *DisassembleText);
      void disassembleTextIX1REL(char *DisassembleText);


      void opcodeMnemonicLDA();
      void opcodeMnemonicSTA();
      void opcodeMnemonicLDX();
      void opcodeMnemonicSTX();

      void mnemonicOperationNA   ();
      void mnemonicOperationBRSET();
      void mnemonicOperationBRCLR();
      void mnemonicOperationBSET ();
      void mnemonicOperationBCLR ();
      void mnemonicOperationBRA  ();
      void mnemonicOperationBRN  ();
      void mnemonicOperationBHI  ();
      void mnemonicOperationBLS  ();
      void mnemonicOperationBCC  ();
      void mnemonicOperationBCS  ();
      void mnemonicOperationBNE  ();
      void mnemonicOperationBEQ  ();
      void mnemonicOperationBHCC ();
      void mnemonicOperationBHCS ();
      void mnemonicOperationBPL  ();
      void mnemonicOperationBMI  ();
      void mnemonicOperationBMC  ();
      void mnemonicOperationBMS  ();
      void mnemonicOperationBIL  ();
      void mnemonicOperationBIH  ();
      void mnemonicOperationNEG  ();
      void mnemonicOperationCBEQ ();
      void mnemonicOperationLDHX ();
      void mnemonicOperationCOM  ();
      void mnemonicOperationLSR  ();
      void mnemonicOperationSTHX ();
      void mnemonicOperationROR  ();
      void mnemonicOperationASR  ();
      void mnemonicOperationLSL  ();
      void mnemonicOperationROL  ();
      void mnemonicOperationDEC  ();
      void mnemonicOperationDBNZ ();
      void mnemonicOperationINC  ();
      void mnemonicOperationTST  ();
      void mnemonicOperationCPHX ();
      void mnemonicOperationMOV  ();
      void mnemonicOperationCLR  ();
      void mnemonicOperationMUL  ();
      void mnemonicOperationDIV  ();
      void mnemonicOperationNSA  ();
      void mnemonicOperationDAA  ();
      void mnemonicOperationRTI  ();
      void mnemonicOperationRTS  ();
      void mnemonicOperationBGND ();
      void mnemonicOperationSWI  ();
      void mnemonicOperationTAP  ();
      void mnemonicOperationTPA  ();
      void mnemonicOperationPUL  ();
      void mnemonicOperationPSH  ();
      void mnemonicOperationSTOP ();
      void mnemonicOperationWAIT ();
      void mnemonicOperationBGE  ();
      void mnemonicOperationBLT  ();
      void mnemonicOperationBGT  ();
      void mnemonicOperationBLE  ();
      void mnemonicOperationTXS  ();
      void mnemonicOperationTSX  ();
      void mnemonicOperationTAX  ();
      void mnemonicOperationCLC  ();
      void mnemonicOperationSEC  ();
      void mnemonicOperationCLI  ();
      void mnemonicOperationSEI  ();
      void mnemonicOperationRSP  ();
      void mnemonicOperationNOP  ();
      void mnemonicOperationPAGE2();
      void mnemonicOperationTXA  ();
      void mnemonicOperationSUB  ();
      void mnemonicOperationCMP  ();
      void mnemonicOperationSBC  ();
      void mnemonicOperationCPX  ();
      void mnemonicOperationAND  ();
      void mnemonicOperationBIT  ();
      void mnemonicOperationLDA  ();
      void mnemonicOperationAIS  ();
      void mnemonicOperationSTA  ();
      void mnemonicOperationEOR  ();
      void mnemonicOperationADC  ();
      void mnemonicOperationORA  ();
      void mnemonicOperationADD  ();
      void mnemonicOperationJMP  ();
      void mnemonicOperationBSR  ();
      void mnemonicOperationJSR  ();
      void mnemonicOperationLDX  ();
      void mnemonicOperationSTX  ();
      void mnemonicOperationAIX  ();

      void setFlagMethodNZ8B();
      void setFlagMethodVNZ8B();
      void setFlagMethodVNZ16B();
      void setFlagMethodVHNZC_ADD_8B();
      void setFlagMethodVHNZC_SUB_8B();
      void setFlagMethodVNZ_INC_8B();
      void setFlagMethodVNZ_DEC_8B();
      void setFlagMethodVNZC_CPHX_16B();

      //typedef void (hcs08Instruction::*opcodeMnemonic_function)();

      //opcodeMnemonic_function opcodeMnemonic_functionArray[85];

      char extendedBytes;
      void (hcs08Instruction::*setOperandAddress)();
      void (hcs08Instruction::*disassembleTextFunction)(char *DisassembleText);
      void (hcs08Instruction::*mnemonicOperation)();
      void (hcs08Instruction::*setFlags)();

      unsigned short operandAddress;

      unsigned char TempResult8bit;
      unsigned short TempResult16bit;

      unsigned char TempMemory8bit;
      unsigned short TempMemory16bit;

      unsigned char TempABeforeOperation;

      unsigned char TempBeforeOperation8bit;
      unsigned short TempBeforeOperation16bit;

      int AlteredNextAddress;
};
#endif // HCS08_INSTRUCTION_H
