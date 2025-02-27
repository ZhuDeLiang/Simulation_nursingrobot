#ifndef Y_BAR_H
#define Y_BAR_H
#include<QWidget>
#include"processbar.h"
#include<QGridLayout>

class y_bar:public QWidget
{
    Q_OBJECT

public:
     y_bar(QWidget *parent=nullptr);
     processbar *bar[4];
     QGridLayout *gl;


};
#endif // Y_BAR_H
