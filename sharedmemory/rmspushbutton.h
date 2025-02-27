#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#pragma execution_character_set("utf-8");

#include <QPushButton>

class RmsPushButton : public QPushButton
{
    Q_OBJECT
public:
    /// 按钮类型
    enum class EType:int
    {
        zero=0,
        /// 浅背景
        LightBg,
        /// 深背景
        DarkBg,
        /// LightBgInfoShower
        LBIS,
        /// DarkBgInfoShower
        DBIS,
        max
    };

    /// 按钮状态
    enum class EStatus:int
    {
        zero=0,
        Error,
        Warning,
        Succeed,
        IsClicked,
        X,
        Gray,
        Normal,
        TransParent,
        max
    };

    /// 按钮类型、无HOVER、父控件(默认浅背景)
    RmsPushButton(int id,EType etp=EType::LightBg,bool bNoHover=false,QWidget *parent = 0);

    /// 宽、高、字号、倒角、ID
    int iWidth=80,iHeight=30,iFontSize=15,iRadius=15,iID=0;

    /// 自定义背景色、滑过色、按下色、已被点击色、错误色、警告色、成功色、备用色
    QString strColor,strHoverColor,strPressedColor,strClickedColor,strErrorColor,strWarningColor,strSucceedColor,strXColor,
    strLBXColor="darkgreen",strDBXColor="darkgreen",strDBISXColor="darkgreen",strLBISXColor="darkgreen";

    /// 浅背景 文字位置、文字颜色
    QString strMyLBTextAligh="center",strMyLBTextColor="white";
    /// DarkBg 文字位置、文字颜色
    QString strMyDBTextAligh="center",strMyDBTextColor="white";
    /// LightBgInfoShower 文字位置、文字颜色
    QString strMyLBISTextAligh="center",strMyLBISTextColor="white";
    /// DarkBgInfoShower 文字位置、文字颜色
    QString strMyDBISTextAligh="center",strMyDBISTextColor="";
    /// 更新自定义设计效果
    void updateCustomDesign();
    /// 设置当前按钮状态
    void setStatus(EStatus s);
    /// 获取当前按钮状态
    EStatus getStatus();
signals:
    void sgnClicked(int id);
    void sgnPressed(int id);
    void sgnReleased(int id);
    void sgnDoubleClicked(int id);
private:
    /// 内部当前样式字符串
    QString strMyStyle="";
    EType eMyType;
    EStatus eMyStatus;
    /// 无鼠标滑过效果
    bool bNoHoverColor=false;
    /// 默认 文字位置、文字颜色
    QString strMyDftTextAligh=strMyLBTextAligh,strMyDftTextColor=strMyLBTextColor;

    /// 浅背景 背景色、滑过色、按下色、已被点击色、错误色、警告色、成功色、备用色
    QString strLBColor="steelblue",strLBHoverColor="teal",strLBPressedColor="darkolivegreen",
    strLBClickedColor="olivedrab",strLBErrorColor="orangered",strLBWarningColor="darkgoldenrod",
    strLBSucceedColor="forestgreen",strLBGrayColor="gray";
    /// DarkBg 背景色、滑过色、按下色、已被点击色、错误色、警告色、成功色、备用色
    QString strDBColor="steelblue",strDBHoverColor="teal",strDBPressedColor="darkolivegreen",
    strDBClickedColor="olive",strDBErrorColor="orangered",strDBWarningColor="darkgoldenrod",
    strDBSucceedColor="forestgreen",strDBGrayColor="gray";
    /// LightBgInfoShower 背景色、滑过色、按下色、已被点击色、错误色、警告色、成功色、备用色
    QString strLBISColor="steelblue",strLBISHoverColor="teal",strLBISPressedColor="darkolivegreen",
    strLBISClickedColor="olivedrab",strLBISErrorColor="orangered",strLBISWarningColor="darkgoldenrod",
    strLBISSucceedColor="forestgreen",strLBISGrayColor="gray";
    /// DarkBgInfoShower 背景色、滑过色、按下色、已被点击色、错误色、警告色、成功色、备用色
    QString strDBISColor="steelblue",strDBISHoverColor="teal",strDBISPressedColor="darkolivegreen",
    strDBISClickedColor="olivedrab",strDBISErrorColor="orangered",strDBISWarningColor="darkgoldenrod",
    strDBISSucceedColor="forestgreen",strDBISGrayColor="gray";
    QString strTransParent="transparent";
    /// 浅背景(默认) 背景色、滑过色、按下色、已被点击色、错误色、警告色、成功色、备用色
    QString strDftColor=strLBColor,strDftHoverColor=strLBHoverColor,strDftPressedColor=strLBPressedColor,
    strDftClickedColor=strLBClickedColor,strDftErrorColor=strLBErrorColor,strDftWarningColor=strLBWarningColor,
    strDftSucceedColor=strLBSucceedColor,strDftXColor=strLBXColor,strDftGrayColor=strLBGrayColor;;

    void getPresetStyleString();
};

inline RmsPushButton::RmsPushButton(int id,RmsPushButton::EType etp,bool bnohover, QWidget *parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    if(parent!=0)
        this->setParent(parent);
    eMyType=etp;
    eMyStatus=EStatus::Normal;
    iID=id;
    bNoHoverColor=bnohover;
    getPresetStyleString();
    updateCustomDesign();

    QObject::connect(this,&QPushButton::clicked,[this](){emit this->sgnClicked(iID);});
}

inline void RmsPushButton::updateCustomDesign()
{
    strMyStyle="QPushButton{width:"+QString::number(iWidth)+";height:"+QString::number(iHeight)+";border-radius:"+
            QString::number(iRadius)+"px;font-size:"+QString::number(iFontSize)+"px;font-weight: bold;";
    strMyStyle+="text-align:"+strMyDftTextAligh+";color:"+strMyDftTextColor+";background:"+strDftColor+";}";
    if(eMyType==EType::LightBg||eMyType==EType::DarkBg)
    {
        if(!bNoHoverColor)
            strMyStyle+="QPushButton:hover{color:"+strMyDftTextColor+";background: "+strDftHoverColor+";}";
        strMyStyle+="QPushButton:pressed {background:"+strDftPressedColor+";}";
    }

    this->setStyleSheet(strMyStyle);
}

inline void RmsPushButton::setStatus(RmsPushButton::EStatus s)
{
    if(s==EStatus::IsClicked)
    {
        if(eMyType==EType::LightBg)
        {
            strDftColor=strLBClickedColor;
        }
        else if(eMyType==EType::DarkBg)
        {
            strDftColor=strDBClickedColor;
        }
        else if(eMyType==EType::LBIS)
        {
            strDftColor=strLBISClickedColor;
        }
        else if(eMyType==EType::DBIS)
        {
            strDftColor=strDBISClickedColor;
        }
        else {}
    }
    else if(s==EStatus::Normal)
    {
        if(eMyType==EType::LightBg)
        {
            strDftColor=strLBColor;
        }

        else if(eMyType==EType::DarkBg)
        {
            strDftColor=strDBColor;
        }
        else if(eMyType==EType::LBIS)
        {
            strDftColor=strLBISColor;
        }
        else if(eMyType==EType::DBIS)
        {
            strDftColor=strDBISColor;
        }
        else {}
    }
    else if (s==EStatus::Succeed)
    {
        if(eMyType==EType::LightBg)
        {
            strDftColor=strLBSucceedColor;
        }

        else if(eMyType==EType::DarkBg)
        {
            strDftColor=strDBSucceedColor;
        }
        else if(eMyType==EType::LBIS)
        {
            strDftColor=strLBISSucceedColor;
        }
        else if(eMyType==EType::DBIS)
        {
            strDftColor=strDBISSucceedColor;
        }
        else {}
    }
    else if (s==EStatus::Warning)
    {
        if(eMyType==EType::LightBg)
        {
            strDftColor=strLBWarningColor;
        }

        else if(eMyType==EType::DarkBg)
        {
            strDftColor=strDBWarningColor;
        }
        else if(eMyType==EType::LBIS)
        {
            strDftColor=strLBISWarningColor;
        }
        else if(eMyType==EType::DBIS)
        {
            strDftColor=strDBISWarningColor;
        }
        else {}
    }
    else if (s==EStatus::Error)
    {
        if(eMyType==EType::LightBg)
        {
            strDftColor=strLBErrorColor;
        }

        else if(eMyType==EType::DarkBg)
        {
            strDftColor=strDBErrorColor;
        }
        else if(eMyType==EType::LBIS)
        {
            strDftColor=strLBISErrorColor;
        }
        else if(eMyType==EType::DBIS)
        {
            strDftColor=strDBISErrorColor;
        }
        else {}
    }
    else if (s==EStatus::X)
    {
        if(eMyType==EType::LightBg)
        {
            strDftColor=strLBXColor;
        }

        else if(eMyType==EType::DarkBg)
        {
            strDftColor=strDBXColor;
        }
        else if(eMyType==EType::LBIS)
        {
            strDftColor=strLBISXColor;
        }
        else if(eMyType==EType::DBIS)
        {
            strDftColor=strDBISXColor;
        }
        else {}
    }
    else if (s==EStatus::Gray)
    {
        if(eMyType==EType::LightBg)
        {
            strDftColor=strLBGrayColor;
        }

        else if(eMyType==EType::DarkBg)
        {
            strDftColor=strDBGrayColor;
        }
        else if(eMyType==EType::LBIS)
        {
            strDftColor=strLBISGrayColor;
        }
        else if(eMyType==EType::DBIS)
        {
            strDftColor=strDBISGrayColor;
        }
        else {}
    }
    else if (s==EStatus::TransParent)
    {
        strDftColor=strTransParent;
        //TODO: SET FONT COLOR
        strMyDftTextColor=strMyLBISTextColor;
    }
    eMyStatus=s;

    updateCustomDesign();
}

inline RmsPushButton::EStatus RmsPushButton::getStatus()
{
    return eMyStatus;
}

inline void RmsPushButton::getPresetStyleString()
{
    if(eMyType==EType::LightBg)
    {
        strMyDftTextAligh=strMyLBTextAligh;
        strMyDftTextColor=strMyLBTextColor;
        strDftColor=strLBColor;
        strDftHoverColor=strLBHoverColor;
        strDftPressedColor=strLBPressedColor;
        strDftClickedColor=strLBClickedColor;
        strDftErrorColor=strLBErrorColor;
        strDftWarningColor=strLBWarningColor;
        strDftSucceedColor=strLBSucceedColor;
        strDftXColor=strLBXColor;
    }

    if(eMyType==EType::DarkBg)
    {
        strMyDftTextAligh=strMyDBTextAligh;
        strMyDftTextColor=strMyDBTextColor;
        strDftColor=strDBColor;
        strDftHoverColor=strDBHoverColor;
        strDftPressedColor=strDBPressedColor;
        strDftClickedColor=strDBClickedColor;
        strDftErrorColor=strDBErrorColor;
        strDftWarningColor=strDBWarningColor;
        strDftSucceedColor=strDBSucceedColor;
        strDftXColor=strDBXColor;
    }

    if(eMyType==EType::LBIS)
    {
        strMyDftTextAligh=strMyLBISTextAligh;
        strMyDftTextColor=strMyLBISTextColor;
        strDftColor=strLBISColor;
        strDftHoverColor=strLBISHoverColor;
        strDftPressedColor=strLBISPressedColor;
        strDftClickedColor=strLBISClickedColor;
        strDftErrorColor=strLBISErrorColor;
        strDftWarningColor=strLBISWarningColor;
        strDftSucceedColor=strLBISSucceedColor;
        strDftXColor=strLBISXColor;
    }

    if(eMyType==EType::DBIS)
    {
        strMyDftTextAligh=strMyDBISTextAligh;
        strMyDftTextColor=strMyDBISTextColor;
        strDftColor=strDBISColor;
        strDftHoverColor=strDBISHoverColor;
        strDftPressedColor=strDBISPressedColor;
        strDftClickedColor=strDBISClickedColor;
        strDftErrorColor=strDBISErrorColor;
        strDftWarningColor=strDBISWarningColor;
        strDftSucceedColor=strDBISSucceedColor;
        strDftXColor=strDBISXColor;
    }
}

#endif // MYPUSHBUTTON_H
