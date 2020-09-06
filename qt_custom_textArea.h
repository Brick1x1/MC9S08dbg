#ifndef QT_CUSTOM_TEXTAREA_H
#define QT_CUSTOM_TEXTAREA_H

#include <QtWidgets>

namespace Ui {
   class qtCustomTextArea;
}

class qtCustomTextArea : public QWidget
{

   Q_OBJECT

public:

   explicit qtCustomTextArea(QWidget *parent = nullptr, QScrollBar *scrollBar = nullptr);
   void setContent(unsigned char *content,int length);

   int interLineHeight = 0;
   int charWidth = 0;

   unsigned char *m_content;
   int m_content_length;

   int lastMouseClickedPosX=0;
   int lastMouseClickedPosY=0;

   int getViewportNoOfLines();
   int getTotalNoOfLines();
   QScrollBar *m_scrollBar;

public slots:

   void scrollBarChanged(int value);

protected:

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *e) override;

private:

   int cursorX=0,cursorY=0;
   bool isHighNibble = 0;
   int cursorBytePos = 0;
   void setCursor(QMouseEvent *e);



   int scrollBarValue;
   int scrollBarMaxValue;
   void WriteViewContent();

};
#endif // QT_CUSTOM_TEXTAREA_H
