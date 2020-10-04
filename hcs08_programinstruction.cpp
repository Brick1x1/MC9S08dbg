#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "hcs08_programinstruction.h"

using namespace std;

hcs08_ProgramInstruction::hcs08_ProgramInstruction(unsigned short p_startAddr , char *p_disassembleText, int p_instructionLength)
{
   startAddr = p_startAddr;
   strcpy(disassembleText,p_disassembleText);
   instructionLength = p_instructionLength;
}
