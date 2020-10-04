#include "qdisassembleview.h"

#include "sim_MC9S08_S08AC60.h"
#include "hcs08_programinstruction.h"

#include <queue>
#include <stack>

QDisassembleView::QDisassembleView(simMC9S08AC60 *p_cpu)
{
   cpu = p_cpu;

   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   scrollBarValue = 0;
   connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrollBarChanged(int)));

   viewport()->setFont(QFont("Courier New"));
   interLineHeight = viewport()->fontMetrics().lineSpacing();
   charWidth = viewport()->fontMetrics().width(QString::fromUtf8("0"));

   char str[] = "----------------------------";
   emptyProgramInst = new hcs08_ProgramInstruction(0,str,0);

}

void QDisassembleView::scrollBarChanged(int value)
{
   scrollBarValue = value;
   //printf("scrollBarValue %d\n",scrollBarValue);
   update();
}

void QDisassembleView::paintEvent(QPaintEvent * /* event */)
{
   scrollBarMaxValue = this->getTotalNoOfLines() - this->getViewportNoOfLines() + 1;
   if(scrollBarMaxValue < 0) scrollBarMaxValue = 0;
   verticalScrollBar()->setMaximum(scrollBarMaxValue);
   verticalScrollBar()->setPageStep(this->getViewportNoOfLines()-1);

   //printf("getTotalNoOfLines: %d, getViewportNoOfLines: %d\n",this->getTotalNoOfLines(),this->getViewportNoOfLines());

   WriteViewContent();
}


int QDisassembleView::getTotalNoOfLines()
{
   return programInstBySerialNo.size();
}


int QDisassembleView::getViewportNoOfLines()
{
   int viewPortNoOfLines = viewport()->height() / this->interLineHeight;
   if((viewport()->height() % this->interLineHeight) > 0) viewPortNoOfLines++;
   return viewPortNoOfLines;
}

void QDisassembleView::keyPressEvent(QKeyEvent * /* e */)
{
}

void QDisassembleView::mousePressEvent(QMouseEvent * /* e */)
{
}

void QDisassembleView::WriteViewContent()
{
   QPainter painter(viewport());

   int i=0;

   painter.setBackgroundMode(Qt::OpaqueMode);

   for(std::map<int, hcs08_ProgramInstruction *>::iterator it=programInstBySerialNo.find(scrollBarValue); it!=programInstBySerialNo.find(scrollBarValue+getViewportNoOfLines()); ++it)
   {

      hcs08_ProgramInstruction *progInst = (hcs08_ProgramInstruction *)(it->second);

      if(progInst->startAddr == cpu->getProgramCounterPrevious())
      {

         painter.setBackground(QColor::fromRgb(0x30,0x8C,0xC6));
         painter.setPen(Qt::white);

         painter.drawText(0,14 +(i++ * interLineHeight),QString::fromStdString(progInst->disassembleText) );

         painter.setBackground(Qt::white);
         painter.setPen(Qt::black);
      }
      else
      {
         painter.drawText(0,14 +(i++ * interLineHeight),QString::fromStdString(progInst->disassembleText) );
      }

   }

}

void QDisassembleView::CPUSingleStep()
{
   cpu->step();
   char str[100];
   char str2[150];

   sprintf(str,"%-4s  %-6s  %s",cpu->getProgramCounterAsText(),cpu->getBytecodeText(),cpu->getDisassemblyText());
   sprintf(str2,"%-28s %-8s %s / %s",str,cpu->getAddressingModeText(),cpu->getConditionCodeRegisterText(),cpu->getCPURegisterText());

   unsigned short PC_prev = cpu->getProgramCounterPrevious();

   if(programInstByAddr.find(PC_prev) == programInstByAddr.end())
      programInstByAddr[cpu->getProgramCounterPrevious()] = new hcs08_ProgramInstruction(PC_prev,str2,cpu->getInstructionLength());


   //Rebuild lines in scrollview
   programInstBySerialNo.clear();

   int lineNo = 0;
   int NextInstructionAddr = 0;
   for(std::map<int, hcs08_ProgramInstruction *>::iterator it=programInstByAddr.begin(); it!=programInstByAddr.end(); ++it)
   {
      hcs08_ProgramInstruction *progInst = (hcs08_ProgramInstruction *)(it->second);
      if(NextInstructionAddr != progInst->startAddr)
         programInstBySerialNo[lineNo++] = emptyProgramInst;

      programInstBySerialNo[lineNo++] = progInst;
      NextInstructionAddr = progInst->startAddr + progInst->instructionLength;

   }

   viewport()->update();
}

void QDisassembleView::DisassembleAll()
{
   char str[100];
   char str2[150];

   // Fetch reset vector
   unsigned short cpuPC = cpu->memory[0xFFFE] * 0x100 + cpu->memory[0xFFFF];

   std::stack<unsigned short> disassembleQueue;
   //disassembleQueue.push(cpuPC);
   disassembleQueue.push(0x1916);

   unsigned char cpuOpcode;

   unsigned short subRoutineStart = 0;


   while(!disassembleQueue.empty())
   {
      cpuPC = disassembleQueue.top();
      disassembleQueue.pop();

      cpu->PC = cpuPC;

      do
      {
         cpuOpcode = cpu->memory[cpu->PC];


         //Add subroutine calls to queue
         if(cpuOpcode == 0xCD)
         {
            subRoutineStart = cpu->memory[cpu->PC + 1] * 256 + cpu->memory[cpu->PC + 2];
            disassembleQueue.push(subRoutineStart);

            printf("%X jsr %x (EXT)\n",cpu->PC,subRoutineStart);
         }

         if(cpuOpcode == 0xCC)
         {
            subRoutineStart = cpu->memory[cpu->PC + 1] * 256 + cpu->memory[cpu->PC + 2];
            disassembleQueue.push(subRoutineStart);

            printf("%X jmp %x (EXT)\n",cpu->PC,subRoutineStart);
         }

         if(cpuOpcode == 0xFD)
         {
            subRoutineStart = cpu->H * 256 + cpu->X;
            disassembleQueue.push(subRoutineStart);

            printf("%X jsr %x (IX)\n",cpu->PC,subRoutineStart);
         }

         cpu->step();


         sprintf(str,"%-4s  %-6s  %s",cpu->getProgramCounterAsText(), cpu->getBytecodeText(), cpu->getDisassemblyText());
         sprintf(str2,"%-28s %-8s %s / %s",str,cpu->getAddressingModeText(), cpu->getConditionCodeRegisterText(), cpu->getCPURegisterText());

         unsigned short PC_prev = cpu->getProgramCounterPrevious();

         if(programInstByAddr.find(PC_prev) == programInstByAddr.end())
            programInstByAddr[cpu->getProgramCounterPrevious()] = new hcs08_ProgramInstruction(PC_prev,str2, cpu->getInstructionLength());

         cpuPC += cpu->getInstructionLength();

         cpu->PC = cpuPC;

      } while(cpuOpcode != 0x81 && cpu->getInstructionLength() > 0);

      if(cpu->getInstructionLength() == 0) {
         std::stack<unsigned short> empty;
         std::swap(disassembleQueue, empty);
      }
   }



   //Rebuild lines in scrollview
   programInstBySerialNo.clear();

   int lineNo = 0;
   int NextInstructionAddr = 0;
   for(std::map<int, hcs08_ProgramInstruction *>::iterator it=programInstByAddr.begin(); it!=programInstByAddr.end(); ++it)
   {
      hcs08_ProgramInstruction *progInst = (hcs08_ProgramInstruction *)(it->second);
      if(NextInstructionAddr != progInst->startAddr)
         programInstBySerialNo[lineNo++] = emptyProgramInst;

      programInstBySerialNo[lineNo++] = progInst;
      NextInstructionAddr = progInst->startAddr + progInst->instructionLength;

   }

   viewport()->update();
}



void QDisassembleView::DisassembleRange(unsigned short start_addr, unsigned short end_addr)
{
   char str[100];
   char str2[150];

   // Fetch reset vector
   unsigned short cpuPC = start_addr;

   unsigned short inst_length = 0;
   cpu->PC = cpuPC;

   do
   {
      cpu->step();

      sprintf(str,"%-4s  %-6s  %s",cpu->getProgramCounterAsText(), cpu->getBytecodeText(), cpu->getDisassemblyText());
      sprintf(str2,"%-28s %-8s %s / %s",str,cpu->getAddressingModeText(), cpu->getConditionCodeRegisterText(), cpu->getCPURegisterText());

      unsigned short PC_prev = cpu->getProgramCounterPrevious();

      if(programInstByAddr.find(PC_prev) == programInstByAddr.end())
         programInstByAddr[cpu->getProgramCounterPrevious()] = new hcs08_ProgramInstruction(PC_prev,str2, cpu->getInstructionLength());

      inst_length = cpu->getInstructionLength();
      cpuPC += inst_length;

      cpu->PC = cpuPC;

   } while(cpuPC < end_addr && inst_length > 0);

   //Rebuild lines in scrollview
   programInstBySerialNo.clear();

   int lineNo = 0;
   for(std::map<int, hcs08_ProgramInstruction *>::iterator it=programInstByAddr.begin(); it!=programInstByAddr.end(); ++it)
   {
      hcs08_ProgramInstruction *progInst = (hcs08_ProgramInstruction *)(it->second);

      programInstBySerialNo[lineNo++] = progInst;

      if(cpu->memory[progInst->startAddr] == 0x81)
         programInstBySerialNo[lineNo++] = emptyProgramInst;

   }

   viewport()->update();
}
