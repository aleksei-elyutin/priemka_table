#-------------------------------------------------
#
# Project created by QtCreator 2017-10-29T20:39:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wtest
TEMPLATE = app

CONFIG += c++11

#INCLUDEPATH+= /usr/include/x86_64-linux-gnu/qt5/
SOURCES += \
    main.cpp\
#        mainwindow.cpp \
#    ../../extra_widgets/stageprogresswidget.cpp \
#    ../../extra_widgets/contractwidget.cpp \
#    ../../sources/contract.cpp \
#    ../../sources/stage.cpp \
#    ../../extra_widgets/monheaderwidget.cpp \
#     ../../extra_widgets/tablewidget.cpp
    mywidget.cpp \
 #   mywidgetbox.cpp


HEADERS  += \
#     ../../extra_widgets/stageprogresswidget.h \
#    ../../extra_widgets/contractwidget.h \
#    ../../headers/contract.h \
#    ../../headers/stage.h \
#    mainwindow.h \
#    ../../extra_widgets/monheaderwidget.h \
#     ../../extra_widgets/tablewidget.h
    mywidget.h \

# mywidgetbox.h

FORMS += \
    form2.ui \
    form1.ui
