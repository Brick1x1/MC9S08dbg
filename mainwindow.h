#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sim_MC9S08_S08AC60.h"
#include "qhexviewedit.h"

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

   QPushButton *m_button;
   QPushButton *m_btn_update_mem_view;

   QHBoxLayout *memViewLayout;
   QPlainTextEdit *plainTextDisassemble;
   QHexViewEdit *hexViewEdit;

   simMC9S08AC60 *cpu;

   void CPUSingleStep();
};

#endif // MAINWINDOW_H
