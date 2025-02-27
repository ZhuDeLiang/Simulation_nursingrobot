#include<pose.h>
pose::pose(QWidget *parent) : QWidget(parent)

{
    if(parent)
    this->setParent(parent);
    gr=new QGridLayout(this);
    int a1,b1,a2,b2;
   for(int i=0;i<6;i++)
   {
       std::stringstream out;
       std::stringstream out1;
       if(i/2==0)
       {
           if(i%2==0)
           {
               out<<"X+";
               out1<<"WX+";
               a1=0;
               a2=0;
               b1=3;
               b2=0;
           }
           else
           {
             out<<"X-";
             out1<<"WX-";
             a1=0;
             a2=1;
             b1=3;
             b2=1;
           }

       }
       if(i/2==1)
       {
           if(i%2==0)
           {
               out<<"Y+";
               out1<<"WY+";
               a1=1;
               a2=0;
               b1=4;
               b2=0;
           }
           else
           {
             out<<"Y-";
             out1<<"WY-";
             a1=1;
             a2=1;
             b1=4;
             b2=1;
           }

       }
       if(i/2==2)
       {
           if(i%2==0)
           {
               out<<"Z+";
               out1<<"WZ+";
               a1=2;
               a2=0;
               b1=5;
               b2=0;
           }
           else
           {
             out<<"Z-";
             out1<<"WZ-";
             a1=2;
             a2=1;
             b1=5;
             b2=1;
           }

       }
       QString Out;
       QString Out1;
       Out=QString::fromStdString(out.str());
        Out1=QString::fromStdString(out1.str());
       pose_control[i]=new RmsPushButton(i,RmsPushButton::EType::DarkBg,false,this);
       joint_control[i]=new RmsPushButton(i,RmsPushButton::EType::DarkBg,false,this);
       pose_control[i]->iHeight=80;
       pose_control[i]->iWidth=30;
       pose_control[i]->iRadius=15;
       pose_control[i]->iFontSize=15;
       joint_control[i]->iHeight=80;
       joint_control[i]->iWidth=30;
       joint_control[i]->iRadius=15;
       joint_control[i]->iFontSize=15;
       pose_control[i]->setText(Out);
       joint_control[i]->setText(Out1);

       gr->addWidget(pose_control[i],a1,a2,1,1);
       gr->addWidget(joint_control[i],b1,b2,1,1);

       connect(pose_control[i],&QPushButton::pressed,this,&pose::sendpose);
       connect(pose_control[i],&QPushButton::released,this,&pose::sendpose);

       connect(joint_control[i],&QPushButton::pressed,this,&pose::sendpose);
       connect(joint_control[i],&QPushButton::released,this,&pose::sendpose);
   }


for(int i=0;i<3;i++)
{

    pose_value[i]=0.0f;
    joint_value[i]=0.0f;
}

}

void pose::sendpose()
{

    if(pose_control[0]->isDown())
    {

        pose_value[0]=1.0f;

    }
    else if(pose_control[1]->isDown())
    {
        pose_value[0]=-1.0f;
    }
    else
    {
         pose_value[0]=0.0f;
    }

    if(pose_control[2]->isDown())
    {

        pose_value[1]=1.0f;

    }
    else if(pose_control[3]->isDown())
    {
        pose_value[1]=-1.0f;
    }
    else
    {
         pose_value[1]=0.0f;
    }


    if(pose_control[4]->isDown())
    {

        pose_value[2]=1.0f;

    }
    else if(pose_control[5]->isDown())
    {
        pose_value[2]=-1.0f;
    }
    else
    {
         pose_value[2]=0.0f;
    }


    if(joint_control[0]->isDown())
    {

        joint_value[0]=1.0f;

    }
    else if(joint_control[1]->isDown())
    {
        joint_value[0]=-1.0f;
    }
    else
    {
         joint_value[0]=0.0f;
    }


    if(joint_control[2]->isDown())
    {

        joint_value[1]=1.0f;

    }
    else if(joint_control[3]->isDown())
    {
        joint_value[1]=-1.0f;
    }
    else
    {
         joint_value[1]=0.0f;
    }


    if(joint_control[4]->isDown())
    {

        joint_value[2]=1.0f;

    }
    else if(joint_control[5]->isDown())
    {
        joint_value[2]=-1.0f;
    }
    else
    {
         joint_value[2]=0.0f;
    }


}
