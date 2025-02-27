#include "skin.h"


skin::skin(QWidget *parent)
    : QWidget(parent)
{
     if(parent)
     {
         this->setParent(parent);
     }
    this->setFixedSize(1920,1080);






     QPalette palette;
     QColor color;
     color.setRgb(255,255,255,120);
     palette.setColor(QPalette::Background,color);


     for(int g=0;g<1024;g++)
     {
        label[g]=new QLabel(this);
        label[g]->setFixedSize(20,20);

        label[g]->setAutoFillBackground(true);
        label[g]->setPalette(palette);
     }

     for(int q=0;q<32;q++)
     {
         for(int e=0;e<32;e++)
         {
            label[32*q+e]->setGeometry(0+20*e,10+20*q,20,20);

         }

     }











}



