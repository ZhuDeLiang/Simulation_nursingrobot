QT       += core gui multimedia  multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barshow.cpp \
    fdb_value.cpp \
    main.cpp \
    mainwindow.cpp \
    pose.cpp \
    processbar.cpp \
    sharedmemory.cpp \
    skin.cpp \
    y_bar.cpp

HEADERS += \
    barshow.h \
    fdb_value.h \
    mainwindow.h \
    pose.h \
    processbar.h \
    rmspushbutton.h \
    sharedmemory.h \
    skin.h \
    y_bar.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture.qrc

