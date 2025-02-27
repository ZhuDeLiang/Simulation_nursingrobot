#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(1920,1080);
    this->setWindowTitle("Nurse");
    this->setWindowIcon(QIcon(":/new/prefix1/robot.png"));
    thread=new wthread;
    qtn=new QTimer(this);
    this->grabKeyboard();
    memset(&rbt_data,0,sizeof(rbt_data));
//    but=new QPushButton(ui->centralwidget);
//    this->but->setGeometry(400,80,70,40);
//    joint=new QPushButton(ui->centralwidget);
//    this->joint->setGeometry(500,80,70,40);
    thread->memory_init();
    QFont font;
    QPalette palette;
    QPixmap pixmap=QPixmap(":/new/prefix1/2.jpg").scaled(this->size());
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
    font.setFamily("KaiTi");
    bar=new barshow(this);
    bar->setGeometry(1100,750,800,230);
    Y_bar=new y_bar(this);
    Y_bar->setGeometry(800,750,240,230);

    l_enable=new QCheckBox(ui->centralwidget);
    r_enable=new QCheckBox(ui->centralwidget);
    y_enable=new QCheckBox(ui->centralwidget);
    POSE_ENABLE[0]=new QCheckBox(ui->centralwidget);
    POSE_ENABLE[1]=new QCheckBox(ui->centralwidget);
    POSE_ENABLE[0]->setGeometry(400,150,70,30);
    POSE_ENABLE[1]->setGeometry(400,190,70,30);
    l_enable->setGeometry(270,230,70,30);
    r_enable->setGeometry(270,190,70,30);
    y_enable->setGeometry(270,150,70,30);
    label_l_enable=new QLabel(ui->centralwidget);
    label_r_enable=new QLabel(ui->centralwidget);
    label_y_enable=new QLabel(ui->centralwidget);
    POSE_ENABLE_LABEL[0]=new QLabel(ui->centralwidget);
    POSE_ENABLE_LABEL[1]=new QLabel(ui->centralwidget);
    POSE_ENABLE_LABEL[0]->setGeometry(300,150,100,30);
    POSE_ENABLE_LABEL[1]->setGeometry(300,190,100,30);
    POSE_ENABLE_LABEL[0]->setText("P_l_Enable");
    POSE_ENABLE_LABEL[1]->setText("P_r_Enable");
    POSE_ENABLE_LABEL[0]->setFont(font);
    POSE_ENABLE_LABEL[1]->setFont(font);
    label_l_enable->setGeometry(180,230,70,30);
    label_l_enable->setText("L_Enable");
    label_l_enable->setFont(font);
    label_r_enable->setGeometry(180,190,70,30);
    label_r_enable->setText("R_Enable");
    label_r_enable->setFont(font);
    label_y_enable->setGeometry(180,150,70,30);
    label_y_enable->setText("Y_Enable");
    label_y_enable->setFont(font);


    player =new  QMediaPlayer(this);
    videoWidget =new QVideoWidget(this);
    videoWidget->setGeometry(1050,150,720,540);
    player->setVideoOutput(videoWidget);
    videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
    player->setMedia(QUrl::fromLocalFile("D:\\QT\\2.mp4"));
    videoWidget->show();
    player->play();

    QFont label_font;
    QPalette label_color;
    QColor label_Color;
    label_Color.setRgb(255,255,255,125);
    label_color.setColor(QPalette::Background,label_Color);

    QPalette label_palcolor;
    QColor color_pal;
    color_pal.setRgb(255,255,255,255);
    label_palcolor.setColor(QPalette::Background,color_pal);
    label_palcolor.setColor(QPalette::WindowText,Qt::blue);
    label_font.setFamily("SongTi");
    label_font.setPointSize(12);
    LABEL[0]=new QLabel(this);
    QString m="Mode";
    LABEL[0]->setText(m.toLocal8Bit());
    LABEL[0]->setGeometry(20,100,120,40);
    LABEL[0]->setFont(label_font);
    LABEL[0]->setPalette(label_color);
    LABEL[0]->setAutoFillBackground(true);
    LABEL[0]->setAlignment(Qt::AlignCenter);

    LABEL[1]=new QLabel(this);
    LABEL[1]->setGeometry(10,270,140,40);
    QString j="Joint_Mode";
    LABEL[1]->setText(j.toLocal8Bit());
    LABEL[1]->setFont(label_font);
    LABEL[1]->setPalette(label_palcolor);
    LABEL[1]->setAutoFillBackground(true);
    LABEL[1]->setAlignment(Qt::AlignCenter);

    LABEL[2]=new QLabel(this);
    LABEL[2]->setGeometry(400,270,140,40);
    QString p="Prepose_Mode";
    LABEL[2]->setText(p.toLocal8Bit());
    LABEL[2]->setFont(label_font);
    LABEL[2]->setPalette(label_palcolor);
    LABEL[2]->setAutoFillBackground(true);
    LABEL[2]->setAlignment(Qt::AlignCenter);

    LABEL[3]=new QLabel(this);
    LABEL[3]->setGeometry(790,270,140,40);
    QString po="Pose_Mode";
    LABEL[3]->setText(po.toLocal8Bit());
    LABEL[3]->setFont(label_font);
    LABEL[3]->setPalette(label_palcolor);
    LABEL[3]->setAutoFillBackground(true);
    LABEL[3]->setAlignment(Qt::AlignCenter);

    LABEL[4]=new QLabel(this);
    LABEL[4]->setGeometry(450,100,120,40);
    QString pi="Hand";
    LABEL[4]->setText(pi.toLocal8Bit());
    LABEL[4]->setFont(label_font);
    LABEL[4]->setPalette(label_color);
    LABEL[4]->setAutoFillBackground(true);
    LABEL[4]->setAlignment(Qt::AlignCenter);

    all=new QLabel(ui->centralwidget);
    this->all->setGeometry(0,270,970,40);
    all->setPalette(label_color);
    all->setAutoFillBackground(true);

//    connect_condition=new QLabel(ui->centralwidget);
//    this->connect_condition->setGeometry(600,80,100,40);
//    this->connect_condition->setText("Disconnect");
//    but_label=new QLabel(ui->centralwidget);
//    this->but_label->setGeometry(380,40,120,40);
//    this->but_label->setText("Connect_share");
//    joint_label_=new QLabel(ui->centralwidget);
//    this->joint_label_->setGeometry(500,40,120,40);
//    this->joint_label_->setText("Send_joint");

    joint_label[12]=new QLabel(ui->centralwidget);
    QString  Out="JointY";
    joint_label[12]->setText(Out);
    joint_label[12]->setFont(font);
    joint_label[12]->setGeometry(450,321+23*12,60,30);

    joint_label[13]=new QLabel(ui->centralwidget);
    QString  Out1="JointK";
    joint_label[13]->setText(Out1);
    joint_label[13]->setFont(font);
    joint_label[13]->setGeometry(610,321+23*12,60,30);



    joint_line[12]=new QLineEdit(ui->centralwidget);
    joint_line[12]->setGeometry(520,321+23*12,70,30);
    this->joint_line[12]->setStyleSheet("QLineEdit {border: 1px solid #A0A0A0;height:60px;border-radius: 15px;padding:0px;margin:0px;border-radius:5px;font-size:""px;color: black;}");

    joint_line[13]=new QLineEdit(ui->centralwidget);
    joint_line[13]->setGeometry(680,321+23*12,70,30);
    this->joint_line[13]->setStyleSheet("QLineEdit {border: 1px solid #A0A0A0;height:60px;border-radius: 15px;padding:0px;margin:0px;border-radius:5px;font-size:""px;color: black;}");

    for(int h=0;h<12;h++)
    {
        if(h%2==0)
        {
           std::stringstream out;
           joint_label[h]=new QLabel(ui->centralwidget);
           out<<"JointL"<<(h+2)/2;
           QString string;
           string=QString::fromStdString(out.str());
           this->joint_label[h]->setGeometry(450,321+23*h,60,30);//40 50
           this->joint_label[h]->setText(string);
           this->joint_label[h]->setFont(font);
           joint_line[h]=new QLineEdit(ui->centralwidget);
           joint_line[h]->setGeometry(520,321+23*h,70,30);
           this->joint_line[h]->setStyleSheet("QLineEdit {border: 1px solid #A0A0A0;height:60px;border-radius: 15px;padding:0px;margin:0px;border-radius:5px;font-size:""px;color: black;}");
        }

        else
        {
           std::stringstream out;
//            joint[h]=new QPushButton(ui->centralwidget);
//            this->joint[h]->setGeometry(340,30+20*h,50,20);
           joint_label[h]=new QLabel(ui->centralwidget);
           out<<"JointR"<<(h+1)/2;
           QString string;
           string=QString::fromStdString(out.str());
           this->joint_label[h]->setGeometry(610,298+23*h,60,30);
           this->joint_label[h]->setText(string);
           this->joint_label[h]->setFont(font);
           joint_line[h]=new QLineEdit(ui->centralwidget);
           joint_line[h]->setGeometry(680,298+23*h,70,30);
           this->joint_line[h]->setStyleSheet("QLineEdit {border: 1px solid #A0A0A0;height:60px;border-radius: 15px;padding:0px;margin:0px;border-radius:5px;font-size:""px;color: black;}");
        }
    }

    for(int i=0;i<6;i++)
    {
        rbt_data.in.cmd_value.current_l_value[i]=0;
        rbt_data.in.cmd_value.current_r_value[i]=0;
        this->rbt_data.in.cmd_value.jog_l_value[i]=0;
        this->rbt_data.in.cmd_value.jog_r_value[i]=0;
        this->rbt_data.in.cmd_value.pose_l_value[i]=0;
        this->rbt_data.in.cmd_value.pose_r_value[i]=0;
        this->rbt_data.in.cmd_value.prepose_l_value[i]=0;
        this->rbt_data.in.cmd_value.prepose_r_value[i]=0;
        this->rbt_data.in.cmd.Enable=0;
        this->rbt_data.in.cmd_value.jog_y_value=0;
        this->rbt_data.in.cmd_value.jog_k_value=0;
        this->rbt_data.in.cmd_value.current_y_value=0;
        this->rbt_data.in.cmd_value.current_k_value=0;
        this->rbt_data.in.cmd_value.prepose_y_value=0;
        this->rbt_data.in.cmd_value.prepose_k_value=0;

      this->rbt_data.in.cmd.Mode=JOINT_CONTROL;

        step[i]=0;
        step[6]=0;
        step[7]=0;
    }


    POSE=new pose(this);
    this->POSE->setGeometry(780,300,200,300);//690 300 200 300
    fdb=new fdb_value(this);
    this->fdb->setGeometry(0,620,1000,380);//10 280 700 350
    joint_check=new QCheckBox(ui->centralwidget);
    JOINT=new QLabel(ui->centralwidget);
    this->JOINT->setGeometry(30,150,70,30);
    this->JOINT->setFont(font);
    this->JOINT->setText("JOINT");
    this->joint_check->setGeometry(110,150,70,30);
//    Skin=new skin(this);
//    this->Skin->setGeometry(1100,100,700,700);
    prepose_check=new QCheckBox(ui->centralwidget);
    this->prepose_check->setGeometry(110,190,70,30);
    PREPOSE=new QLabel(ui->centralwidget);
    this->PREPOSE->setFont(font);
    this->PREPOSE->setText("PREPOSE");
    this->PREPOSE->setGeometry(30,190,70,30);

    pose_check=new QCheckBox(ui->centralwidget);
    this->pose_check->setGeometry(110,230,70,30);
    pose_=new QLabel(ui->centralwidget);
    this->pose_->setFont(font);
    this->pose_->setText("POSE");
    this->pose_->setGeometry(30,230,70,30);

    list=new QComboBox(ui->centralwidget);
    list->setGeometry(220,320,90,40);
    this->list->setStyleSheet("QLineEdit {border: 1px solid #A0A0A0;height:60px;border-radius: 15px;padding:0px;margin:0px;background-color:transparent;border-radius:5px;font-size:""px;color: black;}");
    name=new QLineEdit(ui->centralwidget);
    name->setGeometry(220,390,90,40);
    name->setPlaceholderText("Name");
    name->setAlignment(Qt::AlignCenter);
    go=new RmsPushButton(1,RmsPushButton::EType::LightBg,false,this);
    this->go->setGeometry(330,320,90,40);
    this->name->setStyleSheet("QLineEdit {border: 1px solid #A0A0A0;height:60px;border-radius: 15px;padding:0px;margin:0px;background-color:transparent;border-radius:5px;font-size:""px;color: black;}");
    add=new RmsPushButton(1,RmsPushButton::EType::LightBg,false,this);
    this->add->setGeometry(330,370,90,40);
    this->go->setText("Go");
    this->add->setText("Add");
    prepose_cover=new RmsPushButton(1,RmsPushButton::EType::LightBg,false,this);
    this->prepose_cover->setText("Cover");
    this->prepose_cover->setGeometry(330,420,90,40);
    LABEL[5]=new QLabel(ui->centralwidget);
    LABEL[5]->setGeometry(1250,20,600,80);
    QString skin="视频监测";
    LABEL[5]->setText(skin.toLocal8Bit());
    mode_=new   QLabel(this);
    mode_->setGeometry(300,20,600,80);
    QString datadetect="数据监测&控制";
    mode_->setText(datadetect.toLocal8Bit());
    QFont data;
    data.setFamily("KaiTi");
    data.setPointSize(32);
    mode_->setFont(data);
    LABEL[5]->setFont(data);
    for(int i=0;i<12;i++)
    {
        jog[i]=new RmsPushButton(i,RmsPushButton::EType::LightBg,false,this);
        if(i%2==0)
        {
            int a;
            a=i/2;
           std::stringstream out;
           out<<"jog"<<a+1<<"+";
           QString string;
          string=QString::fromStdString(out.str());
            jog[i]->setGeometry(10,320+23*i,90,30);
            jog[i]->setFont(font);
            jog[i]->setText(string);
        }
        else
        {
            int a;
            a=i/2;
            std::stringstream out;
            out<<"jog"<<a+1<<"-";
            QString string;
           string=QString::fromStdString(out.str());
            jog[i]->setGeometry(110,297+23*i,90,30);
            jog[i]->setFont(font);
            jog[i]->setText(string);

        }

    } 
    for(int i=0;i<3;i++)
    {
        pose_pose_r[i]=0.0f;
        pose_euler_r[i]=0.0f;
        pose_pose_l[i]=0.0f;
        pose_euler_l[i]=0.0f;

    }
    {

        jog[12]=new RmsPushButton(1,RmsPushButton::EType::LightBg,false,this);
        jog[12]->setGeometry(220,505,90,30);
        jog[12]->setFont(font);
        jog[12]->setText("Y+");

        jog[13]=new RmsPushButton(1,RmsPushButton::EType::LightBg,false,this);
        jog[13]->setGeometry(330,505,90,30);
        jog[13]->setFont(font);
        jog[13]->setText("Y-");


        jog[14]=new RmsPushButton(1,RmsPushButton::EType::LightBg,false,this);
        jog[14]->setGeometry(220,550,90,30);
        jog[14]->setFont(font);
        jog[14]->setText("K+");

        jog[15]=new RmsPushButton(1,RmsPushButton::EType::LightBg,false,this);
        jog[15]->setGeometry(330,550,90,30);
        jog[15]->setFont(font);
        jog[15]->setText("K-");

    }
   this->rbt_data.in.cmd.prepose_enable=0;
    for(int i=0;i<16;i++)
    {
    connect(jog[i],&QPushButton::pressed,this,&MainWindow::getjog);
    connect(jog[i],&QPushButton::released,this,&MainWindow::getjog);
    }
     connect(this->POSE_ENABLE[0],&QCheckBox::stateChanged,this,&MainWindow::check_pose_l);
     connect(this->POSE_ENABLE[1],&QCheckBox::stateChanged,this,&MainWindow::check_pose_r);
     connect(this->l_enable,&QCheckBox::stateChanged,this,&MainWindow::check_enable_l);
    connect(this->r_enable,&QCheckBox::stateChanged,this,&MainWindow::check_enable_r);
    connect(this->joint_check,&QCheckBox::stateChanged,this,&MainWindow::check_joint);
    connect(qtn,&QTimer::timeout,this,&MainWindow::send);
    connect(qtn,&QTimer::timeout,thread,&wthread::send);
    connect(this->prepose_check,&QCheckBox::stateChanged,this,&MainWindow::check_prepose);
    connect(this->pose_check,&QCheckBox::stateChanged,this,&MainWindow::check_pose);
    connect(add,&QPushButton::pressed,this,&MainWindow::add_prepose);
    connect(go,&QPushButton::pressed,this,&MainWindow::check_pro);
    connect(go,&QPushButton::released,this,&MainWindow::check_pro);
    connect(qtn,&QTimer::timeout,this,&MainWindow::show_fdb);
    connect(qtn,&QTimer::timeout,this,&MainWindow::show_prepose);
    qtn->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::change()
{


}
void MainWindow::send()
{

     this->rbt_data.in.cmd.Mode=this->mode;

    if(this->rbt_data.in.cmd.prepose_enable==1)
    {
        this->rbt_data.in.cmd_value.prepose_l_value[0]=joint_line[0]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_l_value[1]=joint_line[2]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_l_value[2]=joint_line[4]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_l_value[3]=joint_line[6]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_l_value[4]=joint_line[8]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_l_value[5]=joint_line[10]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_r_value[0]=joint_line[1]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_r_value[1]=joint_line[3]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_r_value[2]=joint_line[5]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_r_value[3]=joint_line[7]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_r_value[4]=joint_line[9]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_r_value[5]=joint_line[11]->text().toInt();

        this->rbt_data.in.cmd_value.prepose_y_value=joint_line[12]->text().toInt();
        this->rbt_data.in.cmd_value.prepose_k_value=joint_line[13]->text().toInt();
    }
     if(joint_check->isChecked())
     {

         for(int i=0;i<6;i++)
         {
            if(l_enable->isChecked())
            {
                 this->rbt_data.in.cmd_value.jog_l_value[i]=step[i];
                this->rbt_data.in.cmd_value.jog_r_value[i]=0.0f;
            }
            else if(r_enable->isChecked())
            {
                this->rbt_data.in.cmd_value.jog_r_value[i]=step[i];
                 this->rbt_data.in.cmd_value.jog_l_value[i]=0.0f;
            }
            else
            {
                this->rbt_data.in.cmd_value.jog_r_value[i]=0.0f;
                 this->rbt_data.in.cmd_value.jog_l_value[i]=0.0f;
            }

         }
     }

     if(pose_check->isChecked())
     {

         if(POSE_ENABLE[0]->isChecked())
         {
             for(int i=0;i<3;i++)
             {

                   this->rbt_data.in.cmd_value.pose_l_value[i]=this->POSE->pose_value[i];
                   this->rbt_data.in.cmd_value.pose_l_value[i+3]=this->POSE->joint_value[i];
                 this->rbt_data.in.cmd_value.pose_r_value[i]=0.f;
                 this->rbt_data.in.cmd_value.pose_r_value[i+3]=0.f;

             }
         }
         else if(POSE_ENABLE[1]->isChecked())
         {

             for(int i=0;i<3;i++)
             {

                   this->rbt_data.in.cmd_value.pose_r_value[i]=this->POSE->pose_value[i];
                   this->rbt_data.in.cmd_value.pose_r_value[i+3]=this->POSE->joint_value[i];
                 this->rbt_data.in.cmd_value.pose_l_value[i]=0.f;
                 this->rbt_data.in.cmd_value.pose_l_value[i+3]=0.f;

             }
         }
         else
         {
             for(int i=0;i<3;i++)
             {

                   this->rbt_data.in.cmd_value.pose_r_value[i]=0.f;
                   this->rbt_data.in.cmd_value.pose_r_value[i+3]=0.f;
                 this->rbt_data.in.cmd_value.pose_l_value[i]=0.f;
                 this->rbt_data.in.cmd_value.pose_l_value[i+3]=0.f;

             }

         }

     }



     if(y_enable->isChecked())
     {
         this->rbt_data.in.cmd_value.jog_y_value=step[6];
          this->rbt_data.in.cmd_value.jog_k_value=step[7];

     }
     else
     {
         this->rbt_data.in.cmd_value.jog_y_value=0.0f;
          this->rbt_data.in.cmd_value.jog_k_value=0.0f;

     }

     for(int i=0;i<6;i++)
     {
        this->thread->input.in.cmd.prepose_enable=this->rbt_data.in.cmd.prepose_enable;
        this->thread->input.in.cmd.Mode=this->rbt_data.in.cmd.Mode;
        this->thread->input.in.cmd_value.prepose_l_value[i]= this->rbt_data.in.cmd_value.prepose_l_value[i];
        this->thread->input.in.cmd_value.prepose_r_value[i]= this->rbt_data.in.cmd_value.prepose_r_value[i];
        this->thread->input.in.cmd_value.jog_l_value[i]= this->rbt_data.in.cmd_value.jog_l_value[i];
        this->thread->input.in.cmd_value.jog_r_value[i]= this->rbt_data.in.cmd_value.jog_r_value[i];
//         rbt_data.step_joint[i]=step[i];

//         qDebug()<<rbt_data.joint_data[i];

       this->thread->input.in.cmd_value.pose_l_value[i]=this->rbt_data.in.cmd_value.pose_l_value[i];
       this->thread->input.in.cmd_value.pose_r_value[i]=this->rbt_data.in.cmd_value.pose_r_value[i];
    }
      this->thread->input.in.cmd_value.jog_y_value= this->rbt_data.in.cmd_value.jog_y_value;
      this->thread->input.in.cmd_value.jog_k_value= this->rbt_data.in.cmd_value.jog_k_value;
     this->thread->input.in.cmd_value.prepose_y_value=this->rbt_data.in.cmd_value.prepose_y_value;
     this->thread->input.in.cmd_value.prepose_k_value=this->rbt_data.in.cmd_value.prepose_k_value;




}
void MainWindow::connectcondition()
{
    if(thread->condition==1)
    {
        this->connect_condition->setText("Connect");
    }
}

void MainWindow::check_joint()
{

    mode=JOINT_CONTROL;
   if(joint_check->isChecked())
   {
       prepose_check->blockSignals(true);
       prepose_check->setCheckState(Qt::CheckState::Unchecked);
       prepose_check->blockSignals(false);

       pose_check->blockSignals(true);
       pose_check->setCheckState(Qt::CheckState::Unchecked);
       pose_check->blockSignals(false);
       for(int i=0;i<14;i++)
       {
           joint_line[i]->setEnabled(false);

       }
       for(int i=0;i<16;i++)
       {

           jog[i]->setEnabled(true);
       }
   }
}
void MainWindow::check_prepose()
{
     mode=PRE_POS_CONTROL;
    if(prepose_check->isChecked())
    {
     joint_check->blockSignals(true);
     joint_check->setCheckState(Qt::CheckState::Unchecked);
     joint_check->blockSignals(false);
     pose_check->blockSignals(true);
     pose_check->setCheckState(Qt::CheckState::Unchecked);
     pose_check->blockSignals(false);
        for(int i=0;i<14;i++)
        {
         joint_line[i]->setEnabled(true);

        }
        for(int i=0;i<16;i++)
        {

         jog[i]->setEnabled(false);
        }
    }
}
void MainWindow::check_pose()
{

      mode=POSE_CONTROL;
     if(pose_check->isChecked())
     {
         prepose_check->blockSignals(true);
         prepose_check->setCheckState(Qt::CheckState::Unchecked);
         prepose_check->blockSignals(false);

         joint_check->blockSignals(true);
         joint_check->setCheckState(Qt::CheckState::Unchecked);
         joint_check->blockSignals(false);



     }
}
void MainWindow::getjog()
{

    if(jog[0]->isDown())
    {
      step[0]=50.f;
    }
    else if(jog[1]->isDown())
    {
      step[0]=-50.f;
    }
    else
    {
        step[0]=0.f;
    }

    if(jog[2]->isDown())
    {
      step[1]=50.f;
    }
    else if(jog[3]->isDown())
    {
      step[1]=-50.f;
    }
    else
    {
        step[1]=0.f;
    }

    if(jog[4]->isDown())
    {
      step[2]=50.f;
    }
    else if(jog[5]->isDown())
    {
      step[2]=-50.f;
    }
    else
    {
        step[2]=0.f;
    }

    if(jog[6]->isDown())
    {
      step[3]=50.f;
    }
    else if(jog[7]->isDown())
    {
      step[3]=-50.f;
    }
    else
    {
        step[3]=0.f;
    }


    if(jog[8]->isDown())
    {
      step[4]=50.f;
    }
    else if(jog[9]->isDown())
    {
      step[4]=-50.f;
    }
    else
    {
        step[4]=0.f;
    }


    if(jog[10]->isDown())
    {
      step[5]=50.f;
    }
    else if(jog[11]->isDown())
    {
      step[5]=-50.f;
    }
    else
    {
        step[5]=0.f;
    }

    if(jog[12]->isDown())
    {
      step[6]=50.f;
    }
    else if(jog[13]->isDown())
    {
      step[6]=-50.f;
    }
    else
    {
        step[6]=0.f;
    }

    if(jog[14]->isDown())
    {
      step[7]=50.f;
    }
    else if(jog[15]->isDown())
    {
      step[7]=-50.f;
    }
    else
    {
        step[7]=0.f;
    }



//    for(int i=0;i<12;i++)
//    {
//      if(i==1)

//        {
//         if(jog[i]->isDown())
//         {
//             this->rbt_data.step_joint[i]=50.f;
//         }
//         else
//         {

//         }

//        }
//        else
//        {
//                 this->rbt_data.step_joint[i/2]=0;
//        }
//    }

}
void MainWindow::check_enable_l()
{
    if(l_enable->isChecked())
    {
        r_enable->blockSignals(true);
        r_enable->setCheckState(Qt::CheckState::Unchecked);
        r_enable->blockSignals(false);

    }

}
void MainWindow::check_enable_r()
{
    if(r_enable->isChecked())
    {
       l_enable->blockSignals(true);
        l_enable->setCheckState(Qt::CheckState::Unchecked);
        l_enable->blockSignals(false);

    }



}
void MainWindow::add_prepose()
{

  if(add->isDown())
  {

      if(name->text()=="")
      {
          QMessageBox::warning(this, tr("名称为空"),"<font size='20' color='red'>名称为空</font>",QMessageBox::Close);
          return ;
      }
  int c;

   c=list->count();
  for(int i=0;i<c;i++)
  {
      if(name->text()== list->itemText(i))
      {
         QMessageBox::warning(this, tr("名称为空"),"<font size='20' color='red'>名称为空</font>",QMessageBox::Close);
        return;
      }
  }


 {
     QString  prename=name->text();
     list->addItem(prename);
     pre[c].name=prename;
    ;
        for(int i=0;i<14;i++)
        {
              pre[c].joint[i]=joint_line[i]->text().toDouble();

        }

        qDebug()<< prename<<            "        "<<c;

 }


  }


}
void MainWindow::check_pro()
{
    if(go->isDown())
    {
        this->rbt_data.in.cmd.prepose_enable=1;
    }
    else
    {
        this->rbt_data.in.cmd.prepose_enable=0;
    }
}
void MainWindow::show_fdb()
{

    memcpy(&rbt_data.out,&this->thread->input.out,sizeof(this->thread->input.out));
    for(int i=0;i<6;i++)
    {
        QString a=QString::number(rbt_data.out.fdb_l_value[i]*r2d,'f',2);
        QString b=QString::number(rbt_data.out.fdb_r_value[i]*r2d,'f',2);
        QString c=QString::number(rbt_data.out.fdb_l_cmt_value[i]*r2d,'f',2);
        QString d=QString::number(rbt_data.out.fdb_r_cmt_value[i]*r2d,'f',2);

        this->fdb->arm_l_label[i]->setText(a);
        this->fdb->arm_r_label[i]->setText(b);
        this->fdb->fdb_value_l[i]->setText(c);
        this->fdb->fdb_value_r[i]->setText(d);
        QString e=QString::number(this->rbt_data.in.cmd_value.jog_l_value[i]*r2d,'f',2);
        QString f=QString::number(this->rbt_data.in.cmd_value.jog_r_value[i]*r2d,'f',2);
        this->fdb->Joint_l_in[i]->setText(e);
        this->fdb->Joint_r_in[i]->setText(f);
        if(i<3)
        { QString g=QString::number(rbt_data.out.fdb_pose_l[i],'f',2);
            QString l=QString::number(rbt_data.out.fdb_pose_r[i],'f',2);

            this->fdb->pose_l_value[i]->setText(g);
             this->fdb->pose_r_value[i]->setText(l);}
        else
        {   QString g=QString::number(rbt_data.out.fdb_pose_l[i]*r2d,'f',2);
            QString l=QString::number(rbt_data.out.fdb_pose_r[i]*r2d,'f',2);

            this->fdb->pose_l_value[i]->setText(g);
             this->fdb->pose_r_value[i]->setText(l);}

    }

    QString g=QString::number(this->rbt_data.out.fdb_y_value*r2d,'f',2);
    this->fdb->y_label[0]->setText(g);
    QString k=QString::number(this->rbt_data.out.fdb_k_value*r2d,'f',2);
    this->fdb->k_label[0]->setText(k);
    for(int i=0;i<6;i++)
    {
        this->bar->bar[i+1]->setCenterText(rbt_data.out.fdb_l_value[i]*r2d);
        this->bar->bar[i+8]->setCenterText(rbt_data.out.fdb_r_value[i]*r2d);
        this->bar->bar[i+1]->setArcAngle(rbt_data.out.fdb_l_value[i]*r2d,processbar::clockwise);
        this->bar->bar[i+8]->setArcAngle(rbt_data.out.fdb_r_value[i]*r2d,processbar::clockwise);


    }
    this->Y_bar->bar[1]->setArcAngle(rbt_data.out.fdb_y_value*r2d,processbar::clockwise);
    this->Y_bar->bar[3]->setArcAngle(rbt_data.out.fdb_k_value*r2d,processbar::clockwise);
    this->Y_bar->bar[1]->setCenterText(rbt_data.out.fdb_y_value*r2d);
    this->Y_bar->bar[3]->setCenterText(rbt_data.out.fdb_k_value*r2d);




}
void MainWindow::show_prepose()
{

    int count=list->count();
    if(count)
    {
        if(prepose_cover->isDown())
          {
            int c=list->currentIndex();
            for(int i=0;i<14;i++)
            {
                joint_line[i]->setText(QString::number(pre[c].joint[i]));

            }
            }

    }


}
void MainWindow::check_pose_l()
{
    if(POSE_ENABLE[0]->isChecked())
    {

        POSE_ENABLE[1]->blockSignals(true);
        POSE_ENABLE[1]->setCheckState(Qt::CheckState::Unchecked);
        POSE_ENABLE[1]->blockSignals(false);

    }

}
void MainWindow::check_pose_r()
{
    if(POSE_ENABLE[1]->isChecked())
    {

        POSE_ENABLE[0]->blockSignals(true);
        POSE_ENABLE[0]->setCheckState(Qt::CheckState::Unchecked);
        POSE_ENABLE[0]->blockSignals(false);

    }

}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
if(event->key()==Qt::Key_0)
{
     step[0]=50.0f;
        qDebug()<<"step[0]  up";

}
  return;

}


void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_0)
    {
         step[0]=0.0f;
         qDebug()<<"00";

    }
    return;


}
