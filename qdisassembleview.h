#ifndef QDISASSEMBLEVIEW_H
#define QDISASSEMBLEVIEW_H

#include "sim_MC9S08_S08AC60.h"
#include "hcs08_programinstruction.h"

#include <QtWidgets>
#include <QtWidgets/qabstractscrollarea.h>

namespace Ui {
   class QDisassembleView;
}

class QDisassembleView : public QAbstractScrollArea
{
      Q_OBJECT

   public:

      QDisassembleView(simMC9S08AC60 *cpu);
      //void setContent(unsigned char *content,int length);

      void CPUSingleStep();
      void DisassembleAll();
      void DisassembleRange(unsigned short start_addr, unsigned short end_addr);

   public slots:

      void scrollBarChanged(int value);

   protected:

      virtual void paintEvent(QPaintEvent *event);
      virtual void keyPressEvent(QKeyEvent *e) override;
      virtual void mousePressEvent(QMouseEvent *e) override;

   private:

      simMC9S08AC60 *cpu;

      int interLineHeight = 0;
      int charWidth = 0;

      std::map<int, hcs08_ProgramInstruction *> programInstByAddr;
      std::map<int, hcs08_ProgramInstruction *> programInstBySerialNo;

      hcs08_ProgramInstruction * emptyProgramInst;

      int noOfLines = 0;

      //int cursorX=0,cursorY=0;
      //bool isHighNibble = 0;
      //int cursorBytePos = 0;

      //unsigned char *m_content;
      //int m_content_length;*/

      int scrollBarValue;
      int scrollBarMaxValue;

      void WriteViewContent();

      //void setCursor(QMouseEvent *e);

      int getViewportNoOfLines();
      int getTotalNoOfLines();

};
#endif // QDISASSEMBLEVIEW_H
