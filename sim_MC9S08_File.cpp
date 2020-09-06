#include "sim_MC9S08_File.h"


int simMC9S08File::ReadS19File(string filename,unsigned char *memory)
{
   fstream newfile;

   int memory_index=0;
   //newfile.open("WAE20351F.S19",ios::in); //open a file to perform read operation using file object
   newfile.open(filename,ios::in); //open a file to perform read operation using file object

   if (newfile.is_open()){   //checking whether the file is open
      string tp;
      while(getline(newfile, tp))
      {
          //read data from file object and put it into string.
          if(tp[0]=='S')
          {
            switch(tp[1])
            {
               case '1':
                  int lineLength = 0;
                  int address = 0;
                  int data = 0;
                  int checksum = 0;
                  int checksumCalculated=0;
                  int lineOffset=2;

                  //cout << tp << "\n"; //print the data of the string

                  lineLength = ReadInt8Bit(tp,lineOffset);
                  lineOffset += 2;
                  checksumCalculated += lineLength;

                  //cout << "/" << lineLength;


                  address = ReadInt16Bit(tp,lineOffset);
                  lineOffset += 4;
                  checksumCalculated += address >> 8;
                  checksumCalculated += address & 0xFF;

                  //cout << "/" << address;

                  memory_index = address;

                  for(int i=0;i<lineLength-3;i++)
                  {
                     data = ReadInt8Bit(tp,lineOffset);
                     lineOffset +=2;
                     checksumCalculated += data;
                     memory[memory_index++]=data;

                     //cout << "/" << data;
                  }

                  checksum = ReadInt8Bit(tp,lineOffset);


                  lineOffset += 2;
                  //cout << "//" << checksum;

                  checksumCalculated = (~checksumCalculated) & 0xFF;
                  //cout << "///" << checksumCalculated;

                  if(checksum != checksumCalculated)
                     return -1;

                  //cout << "\n";

                  break;
            }
          }
      }
      newfile.close(); //close the file object.
      //cout << "Program_index: " << memory_index;

   }
   return 0;
}

// Returns -1 for error
int simMC9S08File::HexcharToInt(char ch)
{
   int val = -1;
   if(ch >= 0x30 && ch <= 0x39) val = ch - 0x30;
   else if(ch >= 0x41 && ch <= 0x46) val = ch - 0x41 + 10;
   else if(ch >= 0x61 && ch <= 0x66) val = ch - 0x61 + 10;

   return val;

}

int simMC9S08File::ReadInt16Bit(string str,int pos)
{
   int val = 0;
   int charVal = 0;
   int i = 0;

   while(i < 4 && charVal >= 0)
   {
      charVal = HexcharToInt(str[pos+i]);
      val = val * 16 + charVal;
      i++;
   }

   if(charVal < 0) return -1;
   else return val;
}


int simMC9S08File::ReadInt8Bit(string str,int pos)
{
   int val = 0;
   int charVal = 0;
   int i = 0;

   while(i < 2 && charVal >= 0)
   {
      charVal = HexcharToInt(str[pos+i]);
      val = val * 16 + charVal;
      i++;
   }

   if(charVal < 0) return -1;
   else return val;
}
