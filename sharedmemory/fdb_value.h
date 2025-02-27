#ifndef FDB_VALUE_H
#define FDB_VALUE_H
#include<QWidget>
#include<QLabel>
#include<QGridLayout>
#include<QFont>
#include<QColor>
#include<QPalette>
#include<Qt>
#include<barshow.h>

class fdb_value:public QWidget
{

public:
    fdb_value(QWidget *parent=nullptr);
    QLabel *arm_r_label[6];
    QLabel *arm_l_label[6];
    QLabel *Joint_r_in[6];
    QLabel *Joint_l_in[6];
    QLabel *fdb_value_r[6];
    QLabel *fdb_value_l[6];
    QLabel *label_monifest[10];
    QLabel *pose_l_value[6];
     QLabel *pose_r_value[6];
     QLabel *y_label[1];
     QLabel *k_label[1];
    QGridLayout *gl;
    QFont font;
    QColor color2;
    QPalette palette1;


};

#endif // FDB_VALUE_H
