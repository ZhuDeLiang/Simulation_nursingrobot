#include<y_bar.h>

y_bar::y_bar(QWidget *parent):QWidget(parent)
{
    if(parent)
        this->setParent(parent);
    gl=new QGridLayout(this);
    for(int i=0;i<2;i++)
    {
        bar[i]=new processbar(this);
        bar[i+2]=new processbar(this);
        bar[i]->setRadius(50);
         bar[i+2]->setRadius(50);

        gl->addWidget(bar[i],0,i,1,1);
        gl->addWidget(bar[i+2],1,i,1,1);

    }
bar[0]->setCenterText("Y");
bar[2]->setCenterText("K");
}
