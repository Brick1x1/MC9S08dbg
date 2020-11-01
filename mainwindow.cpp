#include "sim_MC9S08_File.h"
#include "sim_MC9S08_S08AC60.h"
#include "qhexviewedit.h"
#include "qdisassembleview.h"
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

   // Read program from file and show in hex view
   unsigned char file_content[0x10000];

   //Read S19 file (Memory content)
   simMC9S08File *fileS19 = new simMC9S08File();
   fileS19->ReadS19File("WAE20351F.S19",file_content);

   //Initialize CPU simulation
   cpu = new simMC9S08AC60(file_content);


   QHBoxLayout *queryLayout = new QHBoxLayout();
   queryLayout->addWidget(queryLabel);
   queryLayout->addWidget(queryEdit);
   queryLayout->addWidget(m_button);
   queryLayout->addWidget(m_btn_update_mem_view);

   QHBoxLayout *memViewLayout = new QHBoxLayout();

   //Add disassembly view
   memViewLayout->setSpacing(0);

   disassemblyView = new QDisassembleView(cpu);
   memViewLayout->addWidget(disassemblyView);

   hexViewEdit = new QHexViewEdit();
   hexViewEdit->setFixedWidth(600);
   memViewLayout->addWidget(hexViewEdit);

   QVBoxLayout *mainLayout = new QVBoxLayout();
   mainLayout->addLayout(queryLayout);
   mainLayout->addLayout(memViewLayout);

   queryLayout->setAlignment(Qt::AlignTop);

   ui_area->setLayout(mainLayout);

   hexViewEdit->setContent(cpu->memory,0x10000);

   //180 single step
   /*for(int i=0;i<220;i++)
      disassemblyView->CPUSingleStep();*/

   //disassemblyView->DisassembleAll();

   //disassemblyView->DisassembleRange(0x0870,0x08D4);
   disassemblyView->DisassembleRange(0x0870,0x0E92); //10/10
   disassemblyView->DisassembleRange(0x1860,0x1A00); //10/10

   //disassemblyView->DisassembleRange(0x6200,0xA700);

   disassemblyView->DisassembleRange(0xF600,0xFF80); //10/10

   //disassemblyView->DisassembleRange(0xF600,0xF87C); //10/10
}

void MainWindow::handleButton()
{
   disassemblyView->CPUSingleStep();
   hexViewEdit->viewport()->update();
}


void MainWindow::btnUpdateHexView()
{
}
