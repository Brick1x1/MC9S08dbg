#ifndef HCS08_PROGRAM_INSTRUCTION_H
#define HCS08_PROGRAM_INSTRUCTION_H

using namespace std;

class hcs08_ProgramInstruction
{
   public:
      hcs08_ProgramInstruction(unsigned short p_startAddr , char *p_disassembleText, int p_instructionLength);
      unsigned short startAddr = 0;
      int lineNo = 0;
      char disassembleText[150];
      int instructionLength = 0;

   private:

};
#endif // HCS08_PROGRAM_INSTRUCTION_H
