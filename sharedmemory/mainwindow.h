#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<sharedmemory.h>
#include<QTimer>
#include<QPushButton>
#include<QLabel>
#include<sstream>
#include<QLineEdit>
#include<QDebug>
#include<QCheckBox>
#include<rmspushbutton.h>
#include<pose.h>
#include<fdb_value.h>
#include<QComboBox>
#include<QMessageBox>
#include<processbar.h>
#include<barshow.h>
#include<y_bar.h>
#include<skin.h>
#include <QMediaPlayer>
#include <QVideoWidget>
#include<QUrl>
#include<QWidget>
#include<QKeyEvent>
using namespace std;
#define PI 3.1415
#define r2d 180/PI


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
typedef struct
{

    double joint[14];
    QString name;

}PreposSgl;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void change();
    void send();
    void connectcondition();
    wthread *thread;
    rbt_data rbt_data;
    QTimer *qtn;
    QPushButton *joint;
    QPushButton *but;
    QLabel *connect_condition;
    QLabel *but_label;
     QLabel *joint_label_;
    QLabel *joint_label[14];
    QLineEdit *joint_line[14];
    QCheckBox *joint_check;
    QCheckBox *prepose_check;
    QCheckBox *pose_check;
    QLabel *JOINT;
    QLabel *PREPOSE;
    QLabel *pose_;
    CONTROL_MODE mode;
    pose *POSE;
    fdb_value *fdb;
    QCheckBox *r_enable;
    QCheckBox *l_enable;
    QLabel *label_r_enable;
    QLabel *label_l_enable;
    QLabel *label_y_enable;
    QCheckBox *y_enable;
    QComboBox *list;
    QLineEdit *name;
    RmsPushButton *go;
    RmsPushButton *add;
    PreposSgl pre[10];
    RmsPushButton *prepose_cover;
    int prenumber=0;
    barshow *bar;
    QLabel *mode_;
    QLabel *LABEL[20];
    QCheckBox *POSE_ENABLE[2];
    QLabel *POSE_ENABLE_LABEL[2];

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

public slots:

private:
    Ui::MainWindow *ui;
    void check_joint();
    void check_prepose();
    void check_pose();
    void check_enable_r();
    void check_enable_l();
    RmsPushButton *jog[16];
    void getjog();
    float step[14];
    void getfdb();
    void add_prepose();
    void check_pro();
    void show_fdb();
    void show_prepose();
    void check_pose_l();
    void check_pose_r();
    QLabel *all;
    y_bar *Y_bar;
//    skin *Skin;
    double pose_pose_l[3];
    double pose_pose_r[3];
    double pose_euler_l[3];
    double pose_euler_r[3];
    QMediaPlayer *player;
    QVideoWidget *videoWidget;

};
#endif // MAINWINDOW_H
