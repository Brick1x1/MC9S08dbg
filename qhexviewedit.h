#ifndef QHEXVIEWEDIT_H
#define QHEXVIEWEDIT_H

#include <QtWidgets>
#include <QtWidgets/qabstractscrollarea.h>

namespace Ui {
   class QHexViewEdit;
}

class QHexViewEdit : public QAbstractScrollArea
{
      Q_OBJECT

   public:

      QHexViewEdit();
      void setContent(unsigned char *content,int length);

   public slots:

      void scrollBarChanged(int value);

   protected:

      virtual void paintEvent(QPaintEvent *event);
      virtual void keyPressEvent(QKeyEvent *e) override;
      virtual void mousePressEvent(QMouseEvent *e) override;

   private:

      int interLineHeight = 0;
      int charWidth = 0;

      int cursorX=0,cursorY=0;
      bool isHighNibble = 0;
      int cursorBytePos = 0;

      unsigned char *m_content;
      int m_content_length;

      int scrollBarValue;
      int scrollBarMaxValue;

      void WriteViewContent();

      void setCursor(QMouseEvent *e);

      int getViewportNoOfLines();
      int getTotalNoOfLines();
};
#endif // QHEXVIEWEDIT_H
