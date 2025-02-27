#ifndef PROCESSBAR_H
#define PROCESSBAR_H

#include <QMainWindow>
#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QTimeLine>
#include <QMouseEvent>
#include <QTimerEvent>
class processbar :public QWidget
{
      Q_OBJECT
public:
    processbar(QWidget *parent=nullptr);
    ~ processbar();
    enum Direction {clockwise = -1, anticlockwise = 1};
    void setRadius(int val); //设置半径
    //设置文本
    void setCenterText(const QString &str); // 字符串
    void setCenterText(int val, const QString &catStr = NULL); // 数字
    void setCenterText(double val, const QString &catStr = NULL, int precision = 2);
    // 设置弧线
    void setArcAngle(int angle, Direction direction = clockwise); // 默认方向逆时针
    // 获取画家相关参数
    QPen * getPen();
    QFont * getFont();
protected:
     void paintEvent(QPaintEvent *event); // 重载绘画事件

private:
     double percent;    // 进度百分比，与current相互影响
     int radius;        // 半径大小
     int arcRangle;
     QPen * arcPen;
     QFont * font;
     QPainter * painter;
     QString text;
};

#endif // PROCESSBAR_H
