#ifndef SKIN_H
#define SKIN_H

#include <QMainWindow>
#include<QLabel>
#include<QTimer>
#include<QPalette>
#include<QColor>
#include<QtSerialPort/QtSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<QComboBox>
#include<QPushButton>
#include<QDebug>
#include<QDateTime>
#include<QFileDialog>
#include<QTextStream>
#include<rmspushbutton.h>
 #include <qtextcodec.h>
#include<QGridLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;
class skin: public QWidget
{
    Q_OBJECT

public:
    skin(QWidget *parent = nullptr);

    QLabel *label[1024];




   void label_ini();
  void label_show();
int colorsetr(int c);
int colorsetg(int c);
int colorsetb(int c);
};
#endif // SKIN_H
