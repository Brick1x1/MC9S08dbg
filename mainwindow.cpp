#include "sim_MC9S08_File.h"
#include "sim_MC9S08_S08AC60.h"
#include "qt_custom_textArea.h"

#include "mainwindow.h"

#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   QWidget *ui_area = new QWidget;
   setCentralWidget(ui_area);

   m_button = new QPushButton("Step");
   connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

   m_btn_update_mem_view = new QPushButton("Update mem");
   connect(m_btn_update_mem_view, SIGNAL (released()), this, SLOT (btnUpdateHexView()));


   QLabel *queryLabel = new QLabel(QApplication::translate("nestedlayouts", "Query:"));
   QLineEdit *queryEdit = new QLineEdit();

   QHBoxLayout *queryLayout = new QHBoxLayout();
   queryLayout->addWidget(queryLabel);
   queryLayout->addWidget(queryEdit);
   queryLayout->addWidget(m_button);
   queryLayout->addWidget(m_btn_update_mem_view);

   /*plainTextHexView = new QPlainTextEdit();
   QTextDocument *doc = plainTextHexView->document();
   QFont font = doc->defaultFont();
   font.setFamily("Courier New");
   doc->setDefaultFont(font);*/


   plainTextDisassemble = new QPlainTextEdit();
   QTextDocument *doc = plainTextDisassemble->document();
   QFont font = doc->defaultFont();
   font.setFamily("Courier New");
   doc->setDefaultFont(font);

   char xxxstr[50];
   sprintf(xxxstr,"Font size: %d",font.pointSize());
   plainTextDisassemble->appendPlainText(xxxstr);

   QHBoxLayout *memViewLayout = new QHBoxLayout();

   //Add disassembly view
   memViewLayout->setSpacing(0);
   memViewLayout->addWidget(plainTextDisassemble);

   //memViewLayout->addWidget(plainTextHexView);

   scrollBarV = new QScrollBar(Qt::Vertical);
   scrollBarV->setMinimum(0);

   //Add memory hex view
   hexView = new qtCustomTextArea(nullptr,scrollBarV);
   hexView->setFixedWidth(600);
   hexView->interLineHeight = 18;
   memViewLayout->addWidget(hexView);

   //Add vertical scroll bar
   memViewLayout->addWidget(scrollBarV);


   QVBoxLayout *mainLayout = new QVBoxLayout();
   mainLayout->addLayout(queryLayout);
   mainLayout->addLayout(memViewLayout);

   queryLayout->setAlignment(Qt::AlignTop);

   ui_area->setLayout(mainLayout);

   // Read program from file and show in hex view
   unsigned char file_content[0x10000];

   //Read S19 file (Memory content)
   simMC9S08File *fileS19 = new simMC9S08File();
   fileS19->ReadS19File("WAE20351F.S19",file_content);

   //Initialize CPU simulation
   cpu = new simMC9S08AC60(file_content);

   //Write memory view
   //WriteHexViewContent(cpu->memory,0x10000);

   hexView->setContent(cpu->memory,0x10000);

   //180 single step
   /*for(int i=0;i<180;i++)
      CPUSingleStep();*/

 }



 void MainWindow::handleButton()
 {
   // change the text
   //m_button->setText("Example");
   // resize button
   //m_button->resize(100,100);

   //plainTextDisassemble->appendPlainText(QString::asprintf("PC: %X",cpu->PC));

   //QString qDisassemblyText;
   //qDisassemblyText.sprintf("%s",cpu->getDisassemblyText());
   //plainTextDisassemble->appendPlainText(qDisassemblyText);
   //printf("%s",cpu->getDisassemblyText());

   CPUSingleStep();

   //QString str = QString::fromUtf8(cpu->getProgramCounterText()) + " " + QString::fromUtf8(cpu->getDisassemblyText());
   //plainTextDisassemble.asprintf("%s",str);

}

void MainWindow::CPUSingleStep()
{
   cpu->step();
   char str[100];
   char str2[110];

   sprintf(str,"%-4s  %-6s  %s",cpu->getProgramCounterText(),cpu->getBytecodeText(),cpu->getDisassemblyText());
   sprintf(str2,"%-28s %-8s %s / %s",str,cpu->getAddressingModeText(),cpu->getConditionCodeRegisterText(),cpu->getCPURegisterText());

   plainTextDisassemble->appendPlainText(str2);

   hexView->update();
}

void MainWindow::btnUpdateHexView()
{
}


/*void MainWindow::WriteHexViewContent(unsigned char *program_memory,int program_size)
{
   char buffer [100];
   buffer[99] = 0;
   QString qstr;

   int program_counter = 0;
   int linePosCounter = 0;
   int lineItemNo = 0;

   plainTextHexView->clear();

   while(program_counter < program_size)
   {
       lineItemNo = program_counter%16;

       if(lineItemNo == 0)
       {
          sprintf(&buffer[linePosCounter], " %04X  ", program_counter);
          linePosCounter += 7;
       }

       if(lineItemNo == 8)
       {
          sprintf(&buffer[linePosCounter], "- ");
          linePosCounter += 2;
       }

       sprintf(&buffer[linePosCounter], "%02X ", program_memory[program_counter]);
       linePosCounter += 3;

       if(lineItemNo == 15)
       {
          buffer[linePosCounter]=0;
          qstr = QString::fromStdString(buffer);
          plainTextHexView->appendPlainText(qstr);
          linePosCounter = 0;
       }

       program_counter++;
   }

}*/
