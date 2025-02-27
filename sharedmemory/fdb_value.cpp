#include<fdb_value.h>

fdb_value::fdb_value(QWidget *parent):QWidget(parent)
{

      if(parent)
      this->setParent(parent);
    gl=new QGridLayout(this);
//this->setAttribute(Qt::WA_StyledBackground);
    color2.setRgb(255,255,255,125);

    palette1.setColor(QPalette::Background,color2);
    font.setFamily("KaiTi");
    for(int i=0;i<10;i++)
    {


        label_monifest[i]=new QLabel(this);
        this->label_monifest[i]->setPalette(palette1);
        this->label_monifest[i]->setAutoFillBackground(true);
        this->label_monifest[i]->setFixedSize(80,30);
        this->label_monifest[i]->setFont(font);
        this->label_monifest[i]->setAlignment(Qt::AlignCenter);

         gl->addWidget(label_monifest[i],0,i,1,1);
    }
    for(int i=0;i<6;i++)
    {

       arm_r_label[i]=new QLabel(this);
       this->arm_r_label[i]->setFixedSize(80,30);
       this->arm_r_label[i]->setPalette(palette1);
       this->arm_r_label[i]->setAutoFillBackground(true);
       this->arm_r_label[i]->setFont(font);


       arm_l_label[i]=new QLabel(this);
       this->arm_l_label[i]->setPalette(palette1);
       this->arm_l_label[i]->setAutoFillBackground(true);
       this->arm_l_label[i]->setFixedSize(80,30);
        this->arm_l_label[i]->setFont(font);

       Joint_r_in[i]=new QLabel(this);
       this->Joint_r_in[i]->setPalette(palette1);
       this->Joint_r_in[i]->setAutoFillBackground(true);
       this->Joint_r_in[i]->setFixedSize(80,30);
        this->Joint_r_in[i]->setFont(font);

       Joint_l_in[i]=new QLabel(this);
       this-> Joint_l_in[i]->setPalette(palette1);
       this->Joint_l_in[i]->setAutoFillBackground(true);
       this->Joint_l_in[i]->setFixedSize(80,30);
       this->Joint_l_in[i]->setFont(font);


       fdb_value_r[i]=new QLabel(this);
       this-> fdb_value_r[i]->setPalette(palette1);
       this->fdb_value_r[i]->setAutoFillBackground(true);
       this-> fdb_value_r[i]->setFixedSize(80,30);
       this->fdb_value_r[i]->setFont(font);

       fdb_value_l[i]=new QLabel(this);
       this->fdb_value_l[i]->setPalette(palette1);
       this->fdb_value_l[i]->setAutoFillBackground(true);
       this->fdb_value_l[i]->setFixedSize(80,30);
        this->fdb_value_l[i]->setFont(font);


       pose_l_value[i]=new QLabel(this);
       this->pose_l_value[i]->setPalette(palette1);
       this->pose_l_value[i]->setAutoFillBackground(true);
        this->pose_l_value[i]->setFixedSize(80,30);
       this->pose_l_value[i]->setFont(font);


       pose_r_value[i]=new QLabel(this);
       this->pose_r_value[i]->setPalette(palette1);
       this->pose_r_value[i]->setAutoFillBackground(true);
       this->pose_r_value[i]->setFixedSize(80,30);
       this->pose_r_value[i]->setFont(font);



       gl->addWidget(this->arm_l_label[i],i+1,0,1,1);
       gl->addWidget(this->arm_r_label[i],i+1,1,1,1);
       gl->addWidget(this->Joint_l_in[i],i+1,2,1,1);
       gl->addWidget(this->Joint_r_in[i],i+1,3,1,1);
       gl->addWidget(this->fdb_value_l[i],i+1,4,1,1);
       gl->addWidget(this->fdb_value_r[i],i+1,5,1,1);
       gl->addWidget(this->pose_l_value[i],i+1,6,1,1);
       gl->addWidget(this->pose_r_value[i],i+1,7,1,1);

    }
    {

        y_label[0]=new QLabel(this);
         y_label[0]->setPalette(palette1);
         y_label[0]->setAutoFillBackground(true);
         y_label[0]->setFixedSize(80,30);
         y_label[0]->setFont(font);

         k_label[0]=new QLabel(this);
         k_label[0]->setPalette(palette1);
         k_label[0]->setAutoFillBackground(true);
         k_label[0]->setFixedSize(80,30);
         k_label[0]->setFont(font);

        gl->addWidget(this->y_label[0],1,8,1,1);
        gl->addWidget(this->k_label[0],1,9,1,1);
    }
     this-> label_monifest[0]->setText("fdb_L");
     this-> label_monifest[1]->setText("fdb_R");
     this-> label_monifest[2]->setText("INPUT_L");
     this-> label_monifest[3]->setText("INPUT_R");
     this-> label_monifest[4]->setText("fdb_M_L");
     this-> label_monifest[5]->setText("fdb_M_R");
     this-> label_monifest[6]->setText("pose_R");
     this-> label_monifest[7]->setText("pose_L");
     this-> label_monifest[8]->setText("fdb_y");
    this-> label_monifest[9]->setText("fdb_k");

}
