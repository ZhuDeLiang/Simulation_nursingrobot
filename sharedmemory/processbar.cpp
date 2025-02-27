#include "processbar.h"

processbar::processbar(QWidget *parent)
    : QWidget(parent)
{
    radius =100;
    arcRangle = 360;
     this->resize(radius*2, radius*2);
     painter = new QPainter();

    arcPen = new QPen;
    arcPen->setColor(Qt::white);
    arcPen->setStyle(Qt::SolidLine);
    arcPen->setCapStyle(Qt::RoundCap);
    arcPen->setJoinStyle(Qt::RoundJoin);

    arcPen->setWidthF(10.0);
    font = new QFont();
    font->setPixelSize(30);

   text = "H";

}
processbar::~processbar()
{
    delete font;
    delete arcPen;
    delete painter;
}

void processbar::setRadius(int val)
{
     radius = val;
    this->resize(radius*2, radius*2);
 }
 void processbar::setCenterText(const QString &str)
 {
     text = str;
 }

 void processbar::setCenterText(int val, const QString &catStr)
  {
     text = text.setNum(val) + catStr;
 }

 void processbar::setCenterText(double val, const QString &catStr, int precision)
 {
     text = text.setNum(val, 'f', precision) + catStr;
 }

 void processbar::setArcAngle(int angle, Direction direction)
 {
    arcRangle = angle * direction;
 }

 void processbar::paintEvent(QPaintEvent *event)
 {
     painter->begin(this);
    // 设置渲染模式
     painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
     // 设置画笔
    painter->setPen(*arcPen);
    // 设置文本格式
     painter->setFont(*font);
     // 设置文本显示范围
    QRect textRect(0,0,this->width(), this->height());
    // 绘制文本，在范围内居中显示
     painter->drawText(textRect, Qt::AlignCenter, text);

    int penW = arcPen->width();
   // 绘制圆弧
     painter->drawArc((penW)/2,penW/2,radius*2-penW,radius*2-penW,90*16,arcRangle*16);

     painter->end();
     this->update();
 }

 QPen *processbar::getPen()
 {
     return arcPen;
 }

 QFont *processbar::getFont()
 {
     return font;
 }
