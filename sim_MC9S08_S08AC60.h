#ifndef SIM_MC9S08_S08AC60_H
#define SIM_MC9S08_S08AC60_H

#include "hcs08_instruction.h"
#include "hcs08_programinstruction.h"
#include "hcs08_CPURegisters.h"

using namespace std;

#define AM_NA      0x00  // Not a valid opcode
#define AM_DIR     0x01  // Direct addressing mode
#define AM_EXT     0x02  // Extended addressing mode
#define AM_IMM     0x03  // Immediate addressing mode
#define AM_INH     0x04  // Inherent addressing mode
#define AM_IX0     0x05  // Indexed, no offset addressing mode
#define AM_IX1     0x06  // Indexed, 8-bit offset addressing mode
#define AM_IX2     0x07  // Indexed, 16-bit offset addressing mode
#define AM_IXP     0x08  // Indexed, no offset, post increment addressing mode
#define AM_I1P     0x09  // Indexed, 8-bit offset, post increment addressing mode
#define AM_REL     0x0A  // Relative addressing mode
#define AM_SP1     0x0B  // Stack pointer, 8-bit offset addressing mode
#define AM_SP2     0x0C  // Stack pointer 16-bit offset addressing mode
/*#define AM_DIR_DIR 0x0D  // Move: load Direct, store Direct
#define AM_DIR_IXP 0x0E  // Move: load Direct, store Indexed + 8-bit offset
#define AM_IMM_DIR 0x0F  // Move: load Immediate, store Direct
#define AM_IXP_DIR 0x10  // Move: load Indexed + 8-bit offset, store Direct*/

//Define disassemble function
#define DF_NA         0x00 // Not a valid opcode
#define DF_DIR        0x01 // Direct addressing mode
#define DF_DIRREL     0x02 // Direct addressing mode
#define DF_EXT        0x03 // Extended addressing mode
#define DF_IMM8       0x04 // Immediate addressing mode (8 bit)
#define DF_IMM16      0x05 // Immediate addressing mode (16 bit)
#define DF_INH        0x06 // Inherent addressing mode
#define DF_IX0        0x07 // Indexed, no offset addressing mode
#define DF_IX1        0x08 // Indexed, 8-bit offset addressing mode
#define DF_IX2        0x09 // Indexed, 16-bit offset addressing mode
#define DF_IXP        0x0A // Indexed, no offset, post increment addressing mode
#define DF_I1P        0x0B // Indexed, 8-bit offset, post increment addressing mode
#define DF_REL        0x0C // Relative addressing mode
#define DF_SP1        0x0D // Stack pointer, 8-bit offset addressing mode
#define DF_SP2        0x0E  // Stack pointer 16-bit offset addressing mode
#define DF_DIRDIR     0x0F  // Direct / direct addressing mode
#define DF_DIRIXP     0x10  // Direct / IX+ addressing mode
#define DF_IMMDIR     0x11  // Immidiate / direct addressing mode
#define DF_IXPDIR     0x12  // IX+ / direct addressing mode
#define DF_IMMREL     0x13  // Direct / direct addressing mode
#define DF_I1PREL     0x14  // Direct / IX+ addressing mode
#define DF_IXPREL     0x15  // Immidiate / direct addressing mode
#define DF_SP1REL     0x16  // IX+ / direct addressing mode
#define DF_INHREL     0x17  // Direct / direct addressing mode
#define DF_IX0REL     0x18  // Direct / IX+ addressing mode
#define DF_IX1REL     0x19  // Immidiate / direct addressing mode

//Opcodes
#define IM_NA        0  // Invalid opcode
#define IM_BRSET     1  //
#define IM_BRCLR     2  //
#define IM_BSET      3  //
#define IM_BCLR      4  //
#define IM_BRA       5  //
#define IM_BRN       6  //
#define IM_BHI       7  //
#define IM_BLS       8  //
#define IM_BCC       9  //
#define IM_BCS      10  //
#define IM_BNE      11  //
#define IM_BEQ      12  //
#define IM_BHCC     13  //
#define IM_BHCS     14  //
#define IM_BPL      15  //
#define IM_BMI      16  //
#define IM_BMC      17  //
#define IM_BMS      18  //
#define IM_BIL      19  //
#define IM_BIH      20  //
#define IM_NEG      21  //
#define IM_CBEQ     22  //
#define IM_LDHX     23  //
#define IM_COM      24  //
#define IM_LSR      25  //
#define IM_STHX     26  //
#define IM_ROR      27  //
#define IM_ASR      28  //
#define IM_LSL      29  //
#define IM_ROL      30  //
#define IM_DEC      31  //
#define IM_DBNZ     32  //
#define IM_INC      33  //
#define IM_TST      34  //
#define IM_CPHX     35  //
#define IM_MOV      36  //
#define IM_CLR      37  //
#define IM_MUL      38  //
#define IM_DIV      39  //
#define IM_NSA      40  //
#define IM_DAA      41  //
#define IM_RTI      42  //
#define IM_RTS      43  //
#define IM_BGND     44  //
#define IM_SWI      45  //
#define IM_TAP      46  //
#define IM_TPA      47  //
#define IM_PUL      48  //
#define IM_PSH      49  //
#define IM_STOP     50  //
#define IM_WAIT     51  //
#define IM_BGE      52  //
#define IM_BLT      53  //
#define IM_BGT      54  //
#define IM_BLE      55  //
#define IM_TXS      56  //
#define IM_TSX      57  //
#define IM_TAX      58  //
#define IM_CLC      59  //
#define IM_SEC      60  //
#define IM_CLI      61  //
#define IM_SEI      62  //
#define IM_RSP      63  //
#define IM_NOP      64  //
#define IM_PAGE2    65  //
#define IM_TXA      66  //
#define IM_SUB      67  //
#define IM_CMP      68  //
#define IM_SBC      69  //
#define IM_CPX      70  //
#define IM_AND      71  //
#define IM_BIT      72  //
#define IM_LDA      73  //
#define IM_AIS      74  //
#define IM_STA      75  //
#define IM_EOR      76  //
#define IM_ADC      77  //
#define IM_ORA      78  //
#define IM_ADD      79  //
#define IM_JMP      80  //
#define IM_BSR      81  //
#define IM_JSR      82  //
#define IM_LDX      83  //
#define IM_STX      84  //
#define IM_AIX      85  //

// Defining method for setting flags
#define MFM_NA             0x00  // Invalid opcode
#define MFM_NONE           0x01  // No flags set
#define MFM_VNZ_8B         0x02  // Set flags V = 0, N, Z for 8 bit result
#define MFM_VNZ_16B        0x03  // Set flags V = 0, N, Z for 16 bit result
#define MFM_VHNZC_ADD_8B   0x04  // Set flags V, H, N, Z, C for 8 bit ADD and ADC result
#define MFM_VNZC_SUB_8B    0x05  // Set flags V, N, Z, C for 8 bit SUB and SBC result
#define MFM_VNZ_INC_8B     0x06  // Set flags V, N, Z for 8 bit INC
#define MFM_VNZ_DEC_8B     0x07  // Set flags V, N, Z for 8 bit DEC
#define MFM_VNZC_CPHX_16B  0x08  // Set flags V, N, Z, C for 16 bit CPHX
#define MFM_NZ_8B          0x09  // Set flags N, Z, C for 8 bit


class simMC9S08AC60
{
   public:

      simMC9S08AC60(unsigned char *p_memory);
      ~simMC9S08AC60();

      unsigned char *memory;

      //Contains PC, A, H, X, SP, CCR
      hcs08CPURegisters *CPURegisters;

      hcs08_ProgramInstruction* singleStepNew();

      unsigned short getProgramCounterPrevious();                     

   private:

      unsigned short ProgramCounterPrevious;

      hcs08Instruction *instructions[256];
      hcs08Instruction *instructionsExt[256];
};


#endif // sim_MC9S08_S08AC60_H
