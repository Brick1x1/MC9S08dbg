#include "sim_MC9S08_File.h"
#include "sim_MC9S08_S08AC60.h"
#include "qhexviewedit.h"
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

   plainTextDisassemble = new QPlainTextEdit();
   QTextDocument *doc = plainTextDisassemble->document();
   QFont font = doc->defaultFont();
   font.setFamily("Courier New");
   doc->setDefaultFont(font);

   /*char xxxstr[50];
   sprintf(xxxstr,"Font size: %d",font.pointSize());
   plainTextDisassemble->appendPlainText(xxxstr);*/

   QHBoxLayout *memViewLayout = new QHBoxLayout();

   //Add disassembly view
   memViewLayout->setSpacing(0);
   memViewLayout->addWidget(plainTextDisassemble);

   hexViewEdit = new QHexViewEdit();
   hexViewEdit->setFixedWidth(600);
   memViewLayout->addWidget(hexViewEdit);

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

   hexViewEdit->setContent(cpu->memory,0x10000);

   //180 single step
   /*for(int i=0;i<180;i++)
      CPUSingleStep();*/
}

void MainWindow::handleButton()
{
   CPUSingleStep();
}

void MainWindow::CPUSingleStep()
{
   cpu->step();
   char str[100];
   char str2[110];

   sprintf(str,"%-4s  %-6s  %s",cpu->getProgramCounterText(),cpu->getBytecodeText(),cpu->getDisassemblyText());
   sprintf(str2,"%-28s %-8s %s / %s",str,cpu->getAddressingModeText(),cpu->getConditionCodeRegisterText(),cpu->getCPURegisterText());

   plainTextDisassemble->appendPlainText(str2);

   hexViewEdit->viewport()->update();
}

void MainWindow::btnUpdateHexView()
{
}
