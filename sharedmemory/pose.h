#ifndef POSE_H
#define POSE_H
#include<QWidget>
#include<rmspushbutton.h>
#include<QGridLayout>
#include<sstream>
using namespace std;
class pose:public  QWidget
{

public:
  explicit pose(QWidget *parent = nullptr);
  RmsPushButton *pose_control[6];
  RmsPushButton *joint_control[6];
  QGridLayout *gr;
  double pose_value[3];
  double joint_value[3];
  void sendpose();

};
#endif // POSE_H
