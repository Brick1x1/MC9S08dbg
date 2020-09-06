#include "qt_custom_textArea.h"
#include <QCoreApplication>

qtCustomTextArea::qtCustomTextArea(QWidget *parent, QScrollBar *scrollBar) : QWidget(parent)
{
   m_scrollBar = scrollBar;
   scrollBarValue = 0;
   connect(m_scrollBar, SIGNAL(valueChanged(int)), this, SLOT(scrollBarChanged(int)));

   QFont font = this->font();
   font.setFamily("Courier New");
   this->setFont(font);

   QFontMetrics qFontMetrics(font); // =   this->fontMetrics();
   interLineHeight = qFontMetrics.lineSpacing();
   charWidth = qFontMetrics.width(QString::fromUtf8("0"));

   QPalette pal = palette();

   // set white background
   pal.setColor(QPalette::Background, Qt::white);
   this->setAutoFillBackground(true);
   this->setPalette(pal);

}

void qtCustomTextArea::scrollBarChanged(int value)
{
   scrollBarValue = value;
   update();
}

void qtCustomTextArea::paintEvent(QPaintEvent * /* event */ )
{
   scrollBarMaxValue = this->getTotalNoOfLines() - this->getViewportNoOfLines() + 1;
   m_scrollBar->setMaximum(scrollBarMaxValue);
   m_scrollBar->setPageStep(this->getViewportNoOfLines()-1);

   WriteViewContent();
}

void qtCustomTextArea::keyPressEvent(QKeyEvent *e)
{
   bool refresh = false;

   int keyPressed = e->key();

   if(keyPressed >= Qt::Key_0 && keyPressed <= Qt::Key_9)
   {
      unsigned char num = (keyPressed - 0x30);
      if(isHighNibble == false)
         m_content[cursorBytePos] = (num * 16) + (m_content[cursorBytePos] & 0x0F);
      else
         m_content[cursorBytePos] = (m_content[cursorBytePos] & 0xF0) + num;

      keyPressed = Qt::Key_Right;
   }

   if(keyPressed >= Qt::Key_A && keyPressed <= Qt::Key_F)
   {
      unsigned char num = (keyPressed - 55);
      if(isHighNibble == false)
         m_content[cursorBytePos] = (num * 16) + (m_content[cursorBytePos] & 0x0F);
      else
         m_content[cursorBytePos] = (m_content[cursorBytePos] & 0xF0) + num;

      keyPressed = Qt::Key_Right;
   }

   switch (keyPressed) {

      case Qt::Key_Left:
         if(cursorBytePos == 0 && isHighNibble == false) {
            cursorBytePos = m_content_length-1;
            isHighNibble = true;
            m_scrollBar->setValue(scrollBarMaxValue);
         }
         else {
            if(isHighNibble == true)
               isHighNibble = false;
            else
            {
               cursorBytePos--;
               isHighNibble = true;
            }
         }

         //Adjust view
         if((cursorBytePos/16) < (scrollBarValue + 3) && scrollBarValue > 0)
            scrollBarValue = (cursorBytePos/16) - 3;

         refresh = true;
         break;

      case Qt::Key_Up:
         if(cursorBytePos < 16) {
            cursorBytePos = m_content_length - 16 + cursorBytePos % 16;
            m_scrollBar->setValue(scrollBarMaxValue);
         }
         else {
            cursorBytePos -= 16;
         }

         //Adjust view
         if((cursorBytePos/16) < (scrollBarValue + 3) && scrollBarValue > 0)
            scrollBarValue = (cursorBytePos/16) - 3;

         refresh = true;
         break;

      case Qt::Key_Right:
         if(cursorBytePos == m_content_length-1 && isHighNibble == true) {
            cursorBytePos = 0;
            isHighNibble = false;
            m_scrollBar->setValue(0);
         }
         else {
            if(isHighNibble == false)
               isHighNibble = true;
            else
            {
               cursorBytePos++;
               isHighNibble = false;
            }
         }

         //Adjust view
         if((cursorBytePos/16) > (scrollBarValue + getViewportNoOfLines() - 4) && scrollBarValue < scrollBarMaxValue)
            scrollBarValue = ((cursorBytePos / 16) + 4 - getViewportNoOfLines());

         refresh = true;
         break;

      case Qt::Key_Down:
         if(cursorBytePos + 16 > m_content_length-1) {
            cursorBytePos = cursorBytePos % 16;
            m_scrollBar->setValue(0);
         }
         else {
            cursorBytePos += 16;
         }

         //Adjust view
         if((cursorBytePos/16) > (scrollBarValue + getViewportNoOfLines() - 4) && scrollBarValue < scrollBarMaxValue)
            scrollBarValue = ((cursorBytePos / 16) + 4 - getViewportNoOfLines());

         refresh = true;
         break;
      case Qt::Key_PageUp:
         printf("Key page up\n");
         break;

      default:
         printf("Default\n");
         break;

   }

   if(refresh == true)
      update();

}

void qtCustomTextArea::mousePressEvent(QMouseEvent *e)
{
   //printf("Mouse press event x:%d, y:%d\n",e->x(),e->y());

   setCursor(e);
   setFocus();
   update();
}

void qtCustomTextArea::setCursor(QMouseEvent *e)
{
   cursorX = e->x()/charWidth;
   cursorY = scrollBarValue + (e->y() / interLineHeight);
   //printf("cursorX:%d, cursorY:%d\n",cursorX,cursorY);

   int tempCursorX  = cursorX;
   if(tempCursorX < 7) tempCursorX = 7;
   if(tempCursorX > 55) tempCursorX = 55;
   if(tempCursorX > 29 && tempCursorX < 33) tempCursorX = 29;

   //printf("tempCursorX:%d\n",tempCursorX);

   int charPos;
   int valueLocation;
   isHighNibble = true;

   if(tempCursorX < 30)
   {
      charPos = (tempCursorX - 7) % 3;
      if(charPos == 0)
         isHighNibble = false;

      valueLocation = (tempCursorX - 7) / 3;
   }
   else
   {
      charPos = (tempCursorX - 33) % 3;
      if(charPos == 0)
         isHighNibble = false;

      valueLocation = 8 + ((tempCursorX - 33) / 3);
   }

   cursorBytePos = (cursorY * 16) + valueLocation;

   //Byte pointer outside buffer, set it to length - 1 and set highnibble to true
   if(cursorBytePos >= m_content_length)
   {
      cursorBytePos = m_content_length - 1;
      isHighNibble = true;
   }

   //printf("cursorBytePos:%d, isHighNibble:%d\n",cursorBytePos,isHighNibble);

}


void qtCustomTextArea::setContent(unsigned char *content,int content_length)
{
   m_content = content;
   m_content_length = content_length;
   update();
}

int qtCustomTextArea::getTotalNoOfLines()
{
   int noOfLines = m_content_length / 16;
   if((m_content_length % 16) != 0) noOfLines++;
   return noOfLines;
}

int qtCustomTextArea::getViewportNoOfLines()
{
   int viewPortNoOfLines = this->height() / this->interLineHeight;
   if((this->height() % this->interLineHeight) > 0) viewPortNoOfLines++;
   return viewPortNoOfLines;
}

void qtCustomTextArea::WriteViewContent()
{
   QPainter painter(this);

   char buffer [100];
   buffer[99] = 0;

   int program_counter = scrollBarValue * 16;
   int linePosCounter = 0;
   int lineItemNo = 0;
   int lineNo = 0;

   int program_counter_max = program_counter + (getViewportNoOfLines() * 16);

   if(program_counter_max > m_content_length)
      program_counter_max = m_content_length;

   if(this->hasFocus()) {
      painter.setPen(Qt::red);
      painter.drawRect(0,0,this->width()-1,this->height()-1);
      painter.setPen(Qt::black);
   }

   while(program_counter < program_counter_max)
   {
       lineItemNo = program_counter % 16;

       if(lineItemNo == 0)
       {
          sprintf(&buffer[linePosCounter], " %04X  ", program_counter);
          linePosCounter = 7;
       }

       if(lineItemNo == 8)
       {
          sprintf(&buffer[linePosCounter], "- ");
          linePosCounter += 2;
       }

       sprintf(&buffer[linePosCounter], "%02X ", m_content[program_counter]);
       linePosCounter += 3;

       if(lineItemNo == 15 || program_counter == (program_counter_max-1))
       {
          buffer[linePosCounter]=0;
          painter.drawText(0,14 +(lineNo * interLineHeight),buffer);

          lineNo++;
          linePosCounter = 0;
       }

       program_counter++;
   }

   //draw cursor
   int tempCursorX = cursorBytePos%16;
   int tempCursorY = cursorBytePos/16;

   int tempX;
   int tempY = (tempCursorY - scrollBarValue) * interLineHeight + 17;

   if(tempCursorX < 8)
      tempX = (7 * charWidth) + tempCursorX * (3 * charWidth) + (isHighNibble *charWidth);
   else
      tempX = (33 * charWidth) + ((tempCursorX - 8) * (3 * charWidth)) + (isHighNibble *charWidth);

   if(isHighNibble == false)
      sprintf(buffer, "%1X ", (m_content[cursorBytePos] & 0xF0) >> 4);
   else
      sprintf(buffer, "%1X ", m_content[cursorBytePos] & 0x0F);
   buffer[1]=0;

   painter.setBackgroundMode(Qt::OpaqueMode);
   painter.setBackground(QColor::fromRgb(0xC0,0xC0,0xFF));
   painter.drawText(tempX,tempY-3,buffer);



   painter.setPen(Qt::red);
   painter.drawLine(tempX,tempY,tempX+8,tempY);
   painter.setPen(Qt::black);


}
