#ifndef SIM_MC9S08_FILE_H
#define SIM_MC9S08_FILE_H

#include <string>
#include <fstream>

using namespace std;

class simMC9S08File
{
   public:
      int ReadS19File(string filename,unsigned char *memory);

   private:
      int HexcharToInt(char ch);
      int ReadInt16Bit(string str,int pos);
      int ReadInt8Bit(string str,int pos);
};

#endif // SIM_MC9S08_FILE_H
