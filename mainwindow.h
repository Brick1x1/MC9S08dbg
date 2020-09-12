#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sim_MC9S08_S08AC60.h"
#include "qt_custom_textArea.h"

#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets>

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
   explicit MainWindow(QWidget *parent = 0);
private slots:
   void handleButton();
   void btnUpdateHexView();

private:
   qtCustomTextArea *hexView;

   QPushButton *m_button;
   QPushButton *m_btn_update_mem_view;

   QHBoxLayout *memViewLayout;
   //QPlainTextEdit *plainTextHexView;
   QPlainTextEdit *plainTextDisassemble;
   QScrollBar* scrollBarV;

   simMC9S08AC60 *cpu;

   //void WriteHexViewContent(unsigned char *program_memory,int program_size);

   void CPUSingleStep();

};

#endif // MAINWINDOW_H
