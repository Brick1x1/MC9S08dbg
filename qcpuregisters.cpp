#include "qcpuregisters.h"

//#include "sim_MC9S08_S08AC60.h"
//#include "hcs08_programinstruction.h"
//#include <queue>
//#include <stack>

QCPURegisters::QCPURegisters(hcs08CPURegisters *p_cpuRegisters)
{
   CPURegisters = p_cpuRegisters;
   /*this->setAutoFillBackground(true);
   QPalette qpalet = this->palette();
   qpalet.setColor(QPalette::Window, Qt::blue);
   this->setPalette(qpalet);*/

   this->setFont(QFont("Courier New"));
   //interLineHeight = viewport()->fontMetrics().lineSpacing();
   //charWidth = viewport()->fontMetrics().width(QString::fromUtf8("0"));

}

void QCPURegisters::UpdateGUI()
{
   this->update();
}

void QCPURegisters::paintEvent(QPaintEvent *event)
{
   char strBuf[100];
   QPainter painter(this);

   painter.setBackgroundMode(Qt::OpaqueMode);

   int linespacing = 20;
   int ypos = 20;

   sprintf(strBuf,"PC:  %04X",CPURegisters->PC);
   painter.drawText(10,ypos,QString::fromStdString(strBuf) );
   ypos += linespacing;

   sprintf(strBuf,"SP:  %04X",CPURegisters->SP);
   painter.drawText(10,ypos,QString::fromStdString(strBuf) );
   ypos += linespacing;

   sprintf(strBuf,"H:X: %04X",CPURegisters->H * 0x100 + CPURegisters->X);
   painter.drawText(10,ypos,QString::fromStdString(strBuf) );
   ypos += linespacing;

   sprintf(strBuf,"A:     %02X",CPURegisters->A);
   painter.drawText(10,ypos,QString::fromStdString(strBuf) );
   ypos += linespacing;

   sprintf(strBuf,"H:     %02X",CPURegisters->H);
   painter.drawText(10,ypos,QString::fromStdString(strBuf) );
   ypos += linespacing;

   sprintf(strBuf,"X:     %02X",CPURegisters->X);
   painter.drawText(10,ypos,QString::fromStdString(strBuf) );
   ypos += linespacing;

   sprintf(strBuf,"CCR:   %02X",CPURegisters->getCCR());
   painter.drawText(10,ypos,QString::fromStdString(strBuf) );
   ypos += linespacing;

}
