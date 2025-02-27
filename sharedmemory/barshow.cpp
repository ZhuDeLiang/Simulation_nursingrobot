#include<barshow.h>

barshow::barshow(QWidget *parent):QWidget(parent)
{

    if(parent)
        this->setParent(parent);
       gg=new QGridLayout(this);
    for(int i=0;i<7;i++)
    {
        bar[i]=new processbar(this);
        bar[i+7]=new processbar(this);
        this->bar[i]->setRadius(50);
        this->bar[i+7]->setRadius(50);
        gg->addWidget(bar[i],0,i,1,1);
        gg->addWidget(bar[i+7],1,i,1,1);
    }
    {
        this->bar[0]->setCenterText("L");
        this->bar[7]->setCenterText("R");

    }







}
