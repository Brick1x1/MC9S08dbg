#ifndef QCPUREGISTERS_H
#define QCPUREGISTERS_H

//#include "sim_MC9S08_S08AC60.h"
#include "hcs08_CPURegisters.h"
//#include "hcs08_programinstruction.h"

#include <QtWidgets>


namespace Ui {
   class QCPURegisters;
}

class QCPURegisters : public QWidget
{
      Q_OBJECT

   public:

      QCPURegisters(hcs08CPURegisters *p_cpuRegisters);
      void UpdateGUI();

   public slots:

      //void scrollBarChanged(int value);

   protected:
       void paintEvent(QPaintEvent *event) override;

   private:

      //Contains PC, A, H, X, SP, CCR
      hcs08CPURegisters *CPURegisters;

};
#endif // QCPUREGISTERS_H
