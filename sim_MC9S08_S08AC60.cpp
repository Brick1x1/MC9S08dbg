#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "hcs08_instruction.h"
#include "sim_MC9S08_S08AC60.h"
#include "hcs08_CPURegisters.h"

using namespace std;

simMC9S08AC60::simMC9S08AC60(unsigned char *p_memory)
{
   //Copy memory
   memory = (unsigned char *)malloc(0x10000);
   memcpy(memory,p_memory,0x10000);


   // Instructionlength
   char tempInstNoOfBytes[256] = {     3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, //0x00
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

   //Addressing mode
   char tempInstAddressingMode1st[256] = {    AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR , AM_DIR, //0x00
                                              AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR , AM_DIR, //0x10
                                              AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL, AM_REL , AM_REL, //0x20
                                              AM_DIR, AM_DIR, AM_EXT, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_EXT , AM_DIR, //0x30
                                              AM_INH, AM_IMM, AM_INH, AM_INH, AM_INH, AM_IMM, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_DIR , AM_INH, //0x40
                                              AM_INH, AM_IMM, AM_INH, AM_INH, AM_INH, AM_DIR, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_DIR , AM_INH, //0x50
                                              AM_IX1, AM_I1P, AM_INH, AM_IX1, AM_IX1, AM_IMM, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IMM , AM_IX1, //0x60
                                              AM_IX0, AM_IXP, AM_INH, AM_IX0, AM_IX0, AM_DIR, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IXP , AM_IX0, //0x70
                                              AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_NA , AM_INH , AM_INH, //0x80
                                              AM_REL, AM_REL, AM_REL, AM_REL, AM_INH, AM_INH, AM_EXT, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_INH, AM_NA  , AM_INH, //0x90
                                              AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_IMM, AM_NA , AM_REL, AM_IMM , AM_IMM, //0xA0
                                              AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR, AM_DIR , AM_DIR, //0xB0
                                              AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT, AM_EXT , AM_EXT, //0xC0
                                              AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2, AM_IX2 , AM_IX2, //0xD0
                                              AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1, AM_IX1 , AM_IX1, //0xE0
                                              AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0, AM_IX0 , AM_IX0};//0xF0

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
                                              AM_NA , AM_NA , AM_NA , AM_SP1, AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_NA , AM_SP1, AM_SP1 };//0xF0


   unsigned char tempInstMnemonic[256] = {  IM_BRSET, IM_BRCLR, IM_BRSET, IM_BRCLR, IM_BRSET, IM_BRCLR, IM_BRSET, IM_BRCLR, IM_BRSET, IM_BRCLR, IM_BRSET, IM_BRCLR, IM_BRSET, IM_BRCLR, IM_BRSET, IM_BRCLR, //0x00
                                      IM_BSET , IM_BCLR , IM_BSET , IM_BCLR , IM_BSET , IM_BCLR , IM_BSET , IM_BCLR , IM_BSET , IM_BCLR , IM_BSET , IM_BCLR , IM_BSET , IM_BCLR , IM_BSET , IM_BCLR , //0x10
                                      IM_BRA  , IM_BRN  , IM_BHI  , IM_BLS  , IM_BCC  , IM_BCS  , IM_BNE  , IM_BEQ  , IM_BHCC , IM_BHCS , IM_BPL  , IM_BMI  , IM_BMC  , IM_BMS  , IM_BIL  , IM_BIH  , //0x20
                                      IM_NEG  , IM_CBEQ , IM_LDHX , IM_COM  , IM_LSR  , IM_STHX , IM_ROR  , IM_ASR  , IM_LSL  , IM_ROL  , IM_DEC  , IM_DBNZ , IM_INC  , IM_TST  , IM_CPHX , IM_CLR  , //0x30
                                      IM_NEG  , IM_CBEQ , IM_MUL  , IM_COM  , IM_LSR  , IM_LDHX , IM_ROR  , IM_ASR  , IM_LSL  , IM_ROL  , IM_DEC  , IM_DBNZ , IM_INC  , IM_TST  , IM_MOV  , IM_CLR  , //0x40
                                      IM_NEG  , IM_CBEQ , IM_DIV  , IM_COM  , IM_LSR  , IM_LDHX , IM_ROR  , IM_ASR  , IM_LSL  , IM_ROL  , IM_DEC  , IM_DBNZ , IM_INC  , IM_TST  , IM_MOV  , IM_CLR  , //0x50
                                      IM_NEG  , IM_CBEQ , IM_NSA  , IM_COM  , IM_LSR  , IM_CPHX , IM_ROR  , IM_ASR  , IM_LSL  , IM_ROL  , IM_DEC  , IM_DBNZ , IM_INC  , IM_TST  , IM_MOV  , IM_CLR  , //0x60
                                      IM_NEG  , IM_CBEQ , IM_DAA  , IM_COM  , IM_LSR  , IM_CPHX , IM_ROR  , IM_ASR  , IM_LSL  , IM_ROL  , IM_DEC  , IM_DBNZ , IM_INC  , IM_TST  , IM_MOV  , IM_CLR  , //0x70
                                      IM_RTI  , IM_RTS  , IM_BGND , IM_SWI  , IM_TAP  , IM_TPA  , IM_PUL  , IM_PSH  , IM_PUL  , IM_PSH  , IM_PUL  , IM_PSH  , IM_CLR  , IM_NA   , IM_STOP , IM_WAIT , //0x80
                                      IM_BGE  , IM_BLT  , IM_BGT  , IM_BLE  , IM_TXS  , IM_TSX  , IM_STHX , IM_TAX  , IM_CLC  , IM_SEC  , IM_CLI  , IM_SEI  , IM_RSP  , IM_NOP  , IM_PAGE2, IM_TXA  , //0x90
                                      IM_SUB  , IM_CMP  , IM_SBC  , IM_CPX  , IM_AND  , IM_BIT  , IM_LDA  , IM_AIS  , IM_EOR  , IM_ADC  , IM_ORA  , IM_ADD  , IM_NA   , IM_BSR  , IM_LDX  , IM_AIX  , //0xA0
                                      IM_SUB  , IM_CMP  , IM_SBC  , IM_CPX  , IM_AND  , IM_BIT  , IM_LDA  , IM_STA  , IM_EOR  , IM_ADC  , IM_ORA  , IM_ADD  , IM_JMP  , IM_JSR  , IM_LDX  , IM_STX  , //0xB0
                                      IM_SUB  , IM_CMP  , IM_SBC  , IM_CPX  , IM_AND  , IM_BIT  , IM_LDA  , IM_STA  , IM_EOR  , IM_ADC  , IM_ORA  , IM_ADD  , IM_JMP  , IM_JSR  , IM_LDX  , IM_STX  , //0xC0
                                      IM_SUB  , IM_CMP  , IM_SBC  , IM_CPX  , IM_AND  , IM_BIT  , IM_LDA  , IM_STA  , IM_EOR  , IM_ADC  , IM_ORA  , IM_ADD  , IM_JMP  , IM_JSR  , IM_LDX  , IM_STX  , //0xD0
                                      IM_SUB  , IM_CMP  , IM_SBC  , IM_CPX  , IM_AND  , IM_BIT  , IM_LDA  , IM_STA  , IM_EOR  , IM_ADC  , IM_ORA  , IM_ADD  , IM_JMP  , IM_JSR  , IM_LDX  , IM_STX  , //0xE0
                                      IM_SUB  , IM_CMP  , IM_SBC  , IM_CPX  , IM_AND  , IM_BIT  , IM_LDA  , IM_STA  , IM_EOR  , IM_ADC  , IM_ORA  , IM_ADD  , IM_JMP  , IM_JSR  , IM_LDX  , IM_STX  };//0xF0

   unsigned char tempInstExtMnemonic[256] = {  IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x00
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x10
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x20
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x30
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x40
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x50
                                      IM_NEG  , IM_CBEQ , IM_NA   , IM_COM  , IM_LSR  , IM_NA   , IM_ROR  , IM_ASR  , IM_LSL  , IM_ROL  , IM_DEC  , IM_DBNZ , IM_INC  , IM_TST  , IM_NA   , IM_CLR  , //0x60
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x70
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x80
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , //0x90
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_LDHX , IM_NA   , //0xA0
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_LDHX , IM_NA   , //0xB0
                                      IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_LDHX , IM_NA   , //0xC0
                                      IM_SUB  , IM_CMP  , IM_SBC  , IM_CPX  , IM_AND  , IM_BIT  , IM_LDA  , IM_STA  , IM_EOR  , IM_ADC  , IM_ORA  , IM_ADD  , IM_NA   , IM_NA   , IM_LDX  , IM_STX  , //0xD0
                                      IM_SUB  , IM_CMP  , IM_SBC  , IM_CPX  , IM_AND  , IM_BIT  , IM_LDA  , IM_STA  , IM_EOR  , IM_ADC  , IM_ORA  , IM_ADD  , IM_NA   , IM_NA   , IM_LDX  , IM_STX  , //0xE0
                                      IM_NA   , IM_NA   , IM_NA   , IM_CPHX , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_NA   , IM_LDHX , IM_STHX  };//0xF0


   const char *tempInstMnemonicStr[256] = {  "BRSET0", "BRCLR0", "BRSET1", "BRCLR1", "BRSET2", "BRCLR2", "BRSET3", "BRCLR3", "BRSET4", "BRCLR4", "BRSET5", "BRCLR5", "BRSET6", "BRCLR6", "BRSET7", "BRCLR7", //0x00
                                             "BSET0" , "BCLR0" , "BSET1" , "BCLR1" , "BSET2" , "BCLR2" , "BSET3" , "BCLR3" , "BSET4" , "BCLR4" , "BSET5" , "BCLR5" , "BSET6" , "BCLR6" , "BSET7" , "BCLR7" , //0x10
                                             "BRA"   , "BRN"   , "BHI"   , "BLS"   , "BCC"   , "BCS"   , "BNE"   , "BEQ"   , "BHCC"  , "BHCS"  , "BPL"   , "BMI"   , "BMC"   , "BMS"   , "BIL"   , "BIH"   , //0x20
                                             "NEG"   , "CBEQ"  , "LDHX"  , "COM"   , "LSR"   , "STHX"  , "ROR"   , "ASR"   , "LSL"   , "ROL"   , "DEC"   , "DBNZ"  , "INC"   , "TST"   , "CPHX"  , "CLR"   , //0x30
                                             "NEGA"  , "CBEQA" , "MUL"   , "COMA"  , "LSRA"  , "LDHX"  , "RORA"  , "ASRA"  , "LSLA"  , "ROLA"  , "DECA"  , "DBNZA" , "INCA"  , "TSTA"  , "MOV"   , "CLRA"  , //0x40
                                             "NEGX"  , "CBEQX" , "DIV"   , "COMX"  , "LSRX"  , "LDHX"  , "RORX"  , "ASRX"  , "LSLX"  , "ROLX"  , "DECX"  , "DBNZX" , "INCX"  , "TSTX"  , "MOV"   , "CLRX"  , //0x50
                                             "NEG"   , "CBEQ"  , "NSA"   , "COM"   , "LSR"   , "CPHX"  , "ROR"   , "ASR"   , "LSL"   , "ROL"   , "DEC"   , "DBNZ"  , "INC"   , "TST"   , "MOV"   , "CLR"   , //0x60
                                             "NEG"   , "CBEQ"  , "DAA"   , "COM"   , "LSR"   , "CPHX"  , "ROR"   , "ASR"   , "LSL"   , "ROL"   , "DEC"   , "DBNZ"  , "INC"   , "TST"   , "MOV"   , "CLR"   , //0x70
                                             "RTI"   , "RTS"   , "BGND"  , "SWI"   , "TAP"   , "TPA"   , "PULA"  , "PSHA"  , "PULX"  , "PSHX"  , "PULH"  , "PSHH"  , "CLRH"  , "NA"    , "STOP"  , "WAIT"  , //0x80
                                             "BGE"   , "BLT"   , "BGT"   , "BLE"   , "TXS"   , "TSX"   , "STHX"  , "TAX"   , "CLC"   , "SEC"   , "CLI"   , "SEI"   , "RSP"   , "NOP"   , "PAGE2" , "TXA"   , //0x90
                                             "SUB"   , "CMP"   , "SBC"   , "CPX"   , "AND"   , "BIT"   , "LDA"   , "AIS"   , "EOR"   , "ADC"   , "ORA"   , "ADD"   , "NA"    , "BSR"   , "LDX"   , "AIX"   , //0xA0
                                             "SUB"   , "CMP"   , "SBC"   , "CPX"   , "AND"   , "BIT"   , "LDA"   , "STA"   , "EOR"   , "ADC"   , "ORA"   , "ADD"   , "JMP"   , "JSR"   , "LDX"   , "STX"   , //0xB0
                                             "SUB"   , "CMP"   , "SBC"   , "CPX"   , "AND"   , "BIT"   , "LDA"   , "STA"   , "EOR"   , "ADC"   , "ORA"   , "ADD"   , "JMP"   , "JSR"   , "LDX"   , "STX"   , //0xC0
                                             "SUB"   , "CMP"   , "SBC"   , "CPX"   , "AND"   , "BIT"   , "LDA"   , "STA"   , "EOR"   , "ADC"   , "ORA"   , "ADD"   , "JMP"   , "JSR"   , "LDX"   , "STX"   , //0xD0
                                             "SUB"   , "CMP"   , "SBC"   , "CPX"   , "AND"   , "BIT"   , "LDA"   , "STA"   , "EOR"   , "ADC"   , "ORA"   , "ADD"   , "JMP"   , "JSR"   , "LDX"   , "STX"   , //0xE0
                                             "SUB"   , "CMP"   , "SBC"   , "CPX"   , "AND"   , "BIT"   , "LDA"   , "STA"   , "EOR"   , "ADC"   , "ORA"   , "ADD"   , "JMP"   , "JSR"   , "LDX"   , "STX"   };//0xF0

   const char *tempInstExtMnemonicStr[256] = {"NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x00
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x10
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x20
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x30
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x40
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x50
                                             "NEG"   , "CBEQ"  , "NA"    , "COM"   , "LSR"   , "NA"    , "ROR"   , "ASR"   , "LSL"   , "ROL"   , "DEC"   , "DBNZ"  , "INC"   , "TST"   , "NA"    , "CLR"   , //0x60
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x70
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x80
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , //0x90
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "LDHX"  , "NA"    , //0xA0
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "LDHX"  , "NA"    , //0xB0
                                             "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "LDHX"  , "NA"    , //0xC0
                                             "SUB"   , "CMP "  , "SBC"   , "CPX"   , "AND"   , "BIT"   , "LDA"   , "STA"   , "EOR"   , "ADC"   , "ORA"   , "ADD"   , "NA"    , "NA"    , "LDX"   , "STX"   , //0xD0
                                             "SUB"   , "CMP "  , "SBC"   , "CPX"   , "AND"   , "BIT"   , "LDA"   , "STA"   , "EOR"   , "ADC"   , "ORA"   , "ADD"   , "NA"    , "NA"    , "LDX"   , "STX"   , //0xE0
                                             "NA"    , "NA"    , "NA"    , "CPHX"  , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "NA"    , "LDHX"  , "STHX"  };//0xF0

                                             //Disassemble
   char tempDisassembleFunction[256] = {      DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, DF_DIRREL, //0x00
                                              DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR ,DF_DIR, //0x10
                                              DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL, DF_REL ,DF_REL, //0x20
                                              DF_DIR, DF_DIRREL, DF_EXT, DF_DIR, DF_DIR, DF_DIR  , DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIRREL, DF_DIR, DF_DIR, DF_EXT ,DF_DIR, //0x30
                                              DF_INH, DF_IMMREL, DF_INH, DF_INH, DF_INH, DF_IMM16, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INHREL, DF_INH, DF_INH, DF_DIRDIR ,DF_INH, //0x40
                                              DF_INH, DF_IMMREL, DF_INH, DF_INH, DF_INH, DF_DIR  , DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INHREL, DF_INH, DF_INH, DF_DIRIXP ,DF_INH, //0x50
                                              DF_IX1, DF_I1PREL, DF_INH, DF_IX1, DF_IX1, DF_IMM16, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1REL, DF_IX1, DF_IX1, DF_IMMDIR ,DF_IX1, //0x60
                                              DF_IX0, DF_IXPREL, DF_INH, DF_IX0, DF_IX0, DF_DIR  , DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0REL, DF_IX0, DF_IX0, DF_IXPDIR ,DF_IX0, //0x70
                                              DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_NA , DF_INH ,DF_INH, //0x80
                                              DF_REL, DF_REL, DF_REL, DF_REL, DF_INH, DF_INH, DF_EXT, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_INH, DF_NA  ,DF_INH, //0x90
                                              DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_IMM8, DF_NA , DF_REL, DF_IMM8 ,DF_IMM8, //0xA0
                                              DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR, DF_DIR ,DF_DIR, //0xB0
                                              DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT, DF_EXT ,DF_EXT, //0xC0
                                              DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2, DF_IX2 ,DF_IX2, //0xD0
                                              DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1, DF_IX1 ,DF_IX1, //0xE0
                                              DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0, DF_IX0 ,DF_IX0};//0xF0
   char tempExtDisassembleFunction[256] = {   DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x00
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x10
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x20
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x30
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x40
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x50
                                              DF_SP1, DF_SP1REL, DF_NA , DF_SP1, DF_SP1, DF_NA , DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1REL, DF_SP1, DF_SP1, DF_NA , DF_SP1, //0x60
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x70
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x80
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , //0x90
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_IX0, DF_NA , //0xA0
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_IX2, DF_NA , //0xB0
                                              DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_IX1, DF_NA , //0xC0
                                              DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_SP2, DF_NA , DF_NA , DF_SP2, DF_SP2, //0xD0
                                              DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_SP1, DF_NA , DF_NA , DF_SP1, DF_SP1, //0xE0
                                              DF_NA , DF_NA , DF_NA , DF_SP1, DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_NA , DF_SP1, DF_SP1 };//0xF0


   unsigned char tempMnemonicFlagsMethod[86] = {
                                    MFM_NA,           // IM_NA        0  // Invalid opcode
                                    MFM_NONE,         // IM_BRSET     1  //
                                    MFM_NONE,         // IM_BRCLR     2  //
                                    MFM_NONE,         // IM_BSET      3  //
                                    MFM_NONE,         // IM_BCLR      4  //
                                    MFM_NONE,         // IM_BRA       5  //
                                    MFM_NONE,         // IM_BRN       6  //
                                    MFM_NONE,         // IM_BHI       7  //
                                    MFM_NONE,         // IM_BLS       8  //
                                    MFM_NONE,         // IM_BCC       9  //
                                    MFM_NONE,         // IM_BCS      10  //
                                    MFM_NONE,         // IM_BNE      11  //
                                    MFM_NONE,         // IM_BEQ      12  //
                                    MFM_NONE,         // IM_BHCC     13  //
                                    MFM_NONE,         // IM_BHCS     14  //
                                    MFM_NONE,         // IM_BPL      15  //
                                    MFM_NONE,         // IM_BMI      16  //
                                    MFM_NONE,         // IM_BMC      17  //
                                    MFM_NONE,         // IM_BMS      18  //
                                    MFM_NA,           // IM_BIL      19  //
                                    MFM_NA,           // IM_BIH      20  //
                                    MFM_NONE,         // IM_NEG      21  //
                                    MFM_NONE,         // IM_CBEQ     22  //
                                    MFM_VNZ_16B,      // IM_LDHX     23  //
                                    MFM_VNZ_8B,       // IM_COM      24  //
                                    MFM_NZ_8B,        // IM_LSR      25  //
                                    MFM_VNZ_16B,      // IM_STHX     26  //
                                    MFM_NZ_8B,        // IM_ROR      27  //
                                    MFM_NZ_8B,        // IM_ASR      28  //
                                    MFM_NZ_8B,        // IM_LSL      29  //
                                    MFM_NZ_8B,        // IM_ROL      30  //
                                    MFM_VNZ_DEC_8B,   // IM_DEC      31  //
                                    MFM_NONE,         // IM_DBNZ     32  //
                                    MFM_VNZ_INC_8B,   // IM_INC      33  //
                                    MFM_VNZ_8B,       // IM_TST      34  //
                                    MFM_VNZC_CPHX_16B,// IM_CPHX     35  //
                                    MFM_VNZ_8B,       // IM_MOV      36  //
                                    MFM_NONE,         // IM_CLR      37  //
                                    MFM_NONE,         // IM_MUL      38  //
                                    MFM_NONE,         // IM_DIV      39  //
                                    MFM_NONE,         // IM_NSA      40  //
                                    MFM_VNZ_8B,       // IM_DAA      41  //
                                    MFM_NONE,         // IM_RTI      42  //
                                    MFM_NONE,         // IM_RTS      43  //
                                    MFM_NA,           // IM_BGND     44  //
                                    MFM_NONE,         // IM_SWI      45  //
                                    MFM_NONE,         // IM_TAP      46  //
                                    MFM_NONE,         // IM_TPA      47  //
                                    MFM_NONE,         // IM_PUL      48  //
                                    MFM_NONE,         // IM_PSH      49  //
                                    MFM_NA,           // IM_STOP     50  //
                                    MFM_NA,           // IM_WAIT     51  //
                                    MFM_NONE,         // IM_BGE      52  //
                                    MFM_NONE,         // IM_BLT      53  //
                                    MFM_NONE,         // IM_BGT      54  //
                                    MFM_NONE,         // IM_BLE      55  //
                                    MFM_NONE,         // IM_TXS      56  //
                                    MFM_NONE,         // IM_TSX      57  //
                                    MFM_NONE,         // IM_TAX      58  //
                                    MFM_NONE,         // IM_CLC      59  //
                                    MFM_NONE,         // IM_SEC      60  //
                                    MFM_NONE,         // IM_CLI      61  //
                                    MFM_NONE,         // IM_SEI      62  //
                                    MFM_NONE,         // IM_RSP      63  //
                                    MFM_NONE,         // IM_NOP      64  //
                                    MFM_NA,           // IM_PAGE2    65  //
                                    MFM_NONE,         // IM_TXA      66  //
                                    MFM_VNZC_SUB_8B,  // IM_SUB      67  //
                                    MFM_VNZC_SUB_8B,  // IM_CMP      68  //
                                    MFM_VNZC_SUB_8B,  // IM_SBC      69  //
                                    MFM_VNZC_SUB_8B,  // IM_CPX      70  //
                                    MFM_VNZ_8B,       // IM_AND      71  //
                                    MFM_VNZ_8B,       // IM_BIT      72  //
                                    MFM_VNZ_8B,       // IM_LDA  73  //
                                    MFM_NONE,         // IM_AIS      74  //
                                    MFM_VNZ_8B,       // IM_STA      75  //
                                    MFM_VNZ_8B,       // IM_EOR      76  //
                                    MFM_VHNZC_ADD_8B, // IM_ADC      77  //
                                    MFM_VNZ_8B,       // IM_ORA      78  //
                                    MFM_VHNZC_ADD_8B, // IM_ADD      79  //
                                    MFM_NONE,         // IM_JMP      80  //
                                    MFM_NONE,         // IM_BSR      81  //
                                    MFM_NONE,         // IM_JSR      82  //
                                    MFM_VNZ_8B,       // IM_LDX      83  //
                                    MFM_VNZ_8B,       // IM_STX     84  //
                                    MFM_NONE };       // IM_AIX      85 //


   CPURegisters = new hcs08CPURegisters();

   for(int i=0; i < 256; i++)
   {
      instructions[i]    = new hcs08Instruction(i,memory, tempInstNoOfBytes[i]   , 0, tempInstAddressingMode1st[i]   ,CPURegisters,tempInstMnemonic[i]    ,tempMnemonicFlagsMethod[tempInstMnemonic[i]]    ,tempInstMnemonicStr[i]    ,tempDisassembleFunction[i]    );
      instructionsExt[i] = new hcs08Instruction(i,memory, tempInstExtNoOfBytes[i], 1, tempInstExtAddressingMode1st[i],CPURegisters,tempInstExtMnemonic[i] ,tempMnemonicFlagsMethod[tempInstExtMnemonic[i]] ,tempInstExtMnemonicStr[i] ,tempExtDisassembleFunction[i] );
   }


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

   CPURegisters->A = 0; // ACCUMULATOR
   CPURegisters->H = 0; // INDEX REGISTER (HIGH)
   CPURegisters->X = 0; // INDEX REGISTER (LOW)
   CPURegisters->SP = 0; // STACK POINTER
   CPURegisters->PC = 0; // PROGRAM COUNTER

   // CONDITION CODE REGISTER
   CPURegisters->STATUS_C = 0; // bit 0 - CARRY
   CPURegisters->STATUS_Z = 0; // bit 1 - CCR_ZERO
   CPURegisters->STATUS_N = 0; // bit 2 - CCR_NEGATIVE
   CPURegisters->STATUS_I = 0; // bit 3 - CCR_INTERRUPT_MASK
   CPURegisters->STATUS_H = 0; // bit 4 - CCR_HALF_CARRY
   CPURegisters->STATUS_V = 0; // bit 7 - CCR_TWO_S_COMPLEMENT_OVERFLOW
   // Fetch reset vector
   CPURegisters->PC = memory[0xFFFE] * 0x100 + memory[0xFFFF];

   //Debug
   //PC = 0xF62A; // PROGRAM COUNTER
   //PC = 0xF863;

}

hcs08_ProgramInstruction* simMC9S08AC60::singleStepNew()
{
   unsigned char opCode = memory[CPURegisters->PC];

   //printf("opCode: %X\n",opCode);

   hcs08Instruction *inst;
   if(opCode != 0x9E)
   {
      inst = instructions[opCode];
   }
   else
   {
      opCode = memory[CPURegisters->PC + 1];
      inst = instructionsExt[opCode];
   }

   char strBytecodeText[20] = { 0 };
   char strDisassembleText[60] = { 0 };
   char strAddressingModeText[20] = { 0 };
   char strCCRAsText[40] = { 0 };
   char strRegistersAsText[60] = { 0 };

   unsigned short ProgramCounter = CPURegisters->PC;

   ProgramCounterPrevious = ProgramCounter;

   inst->getBytecodeText(strBytecodeText);
   inst->DisassembleText(strDisassembleText);
   inst->getAddressingModeAsText(strAddressingModeText);

   inst->Execute();

   CPURegisters->getCCRAsText(strCCRAsText);
   CPURegisters->getRegistersAsText(strRegistersAsText);

   char str[100];
   char str2[150];
   sprintf(str,"%04X  %-12s  %s",ProgramCounter,strBytecodeText,strDisassembleText);
   sprintf(str2,"%-38s %-10s %s / %s",str,strAddressingModeText,strCCRAsText,strRegistersAsText);

   //printf("%s\n",str2);

   return new hcs08_ProgramInstruction(ProgramCounter,str2,inst->getInstructionLength());
}

unsigned short simMC9S08AC60::getProgramCounterPrevious()
{
   return ProgramCounterPrevious;
}

simMC9S08AC60::~simMC9S08AC60()
{
   //Delete memory
   delete(memory);
}
