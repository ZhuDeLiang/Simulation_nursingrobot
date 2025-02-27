#ifndef BARSHOW_H
#define BARSHOW_H
#include<QWidget>
#include"processbar.h"
#include<QGridLayout>

class barshow :public QWidget
{
    Q_OBJECT
 public:
    barshow(QWidget *parent=nullptr);
    processbar *bar[14];

    QGridLayout *gg;


};
#endif // BARSHOW_H
