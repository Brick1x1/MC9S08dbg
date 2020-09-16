#include "qhexviewedit.h"


QHexViewEdit::QHexViewEdit()
{
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   scrollBarValue = 0;
   connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrollBarChanged(int)));

   viewport()->setFont(QFont("Courier New"));
   interLineHeight = viewport()->fontMetrics().lineSpacing();
   charWidth = viewport()->fontMetrics().width(QString::fromUtf8("0"));

   // set white background
   /*QPalette pal = palette();
   pal.setColor(QPalette::Background, Qt::white);
   viewport()->setAutoFillBackground(true);
   viewport()->setPalette(pal);*/
}

void QHexViewEdit::scrollBarChanged(int value)
{
   scrollBarValue = value;
   update();
}

void QHexViewEdit::paintEvent(QPaintEvent * /* event */)
{
   scrollBarMaxValue = this->getTotalNoOfLines() - this->getViewportNoOfLines() + 1;
   verticalScrollBar()->setMaximum(scrollBarMaxValue);
   verticalScrollBar()->setPageStep(this->getViewportNoOfLines()-1);

   //printf("getTotalNoOfLines: %d, getViewportNoOfLines: %d\n",this->getTotalNoOfLines(),this->getViewportNoOfLines());
   WriteViewContent();
}

void QHexViewEdit::keyPressEvent(QKeyEvent *e)
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
            verticalScrollBar()->setValue(scrollBarMaxValue);
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
            verticalScrollBar()->setValue(scrollBarMaxValue);
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
            verticalScrollBar()->setValue(0);
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
            verticalScrollBar()->setValue(0);
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
      viewport()->update();

}

void QHexViewEdit::mousePressEvent(QMouseEvent *e)
{
   //printf("Mouse press event x:%d, y:%d\n",e->x(),e->y());
   setCursor(e);
   setFocus();
   viewport()->update();
}

void QHexViewEdit::setContent(unsigned char *content,int content_length)
{
   m_content = content;
   m_content_length = content_length;
   update();
}

void QHexViewEdit::WriteViewContent()
{
   QPainter painter(viewport());

   char buffer [100];
   buffer[99] = 0;

   int program_counter = scrollBarValue * 16;
   int linePosCounter = 0;
   int lineItemNo = 0;
   int lineNo = 0;

   int program_counter_max = program_counter + (getViewportNoOfLines() * 16);

   if(program_counter_max > m_content_length)
      program_counter_max = m_content_length;

   /*if(this->hasFocus()) {
      painter.setPen(Qt::red);
      painter.drawRect(0,0,viewport()->width()-1,viewport()->height()-1);
      painter.setPen(Qt::black);
   }*/

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
   //painter.setBackground(QColor::fromRgb(0xC0,0xC0,0xFF));
   painter.setBackground(QColor::fromRgb(0x30,0x8C,0xC6));
   //painter.setBackground(Qt::blue);
   painter.setPen(Qt::white);
   painter.drawText(tempX,tempY-3,buffer);
}

void QHexViewEdit::setCursor(QMouseEvent *e)
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

int QHexViewEdit::getTotalNoOfLines()
{
   int noOfLines = m_content_length / 16;
   if((m_content_length % 16) != 0) noOfLines++;
   return noOfLines;
}

int QHexViewEdit::getViewportNoOfLines()
{
   int viewPortNoOfLines = viewport()->height() / this->interLineHeight;
   if((viewport()->height() % this->interLineHeight) > 0) viewPortNoOfLines++;
   return viewPortNoOfLines;
}
