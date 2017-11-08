#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T15:25:38
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = priemka_table
TEMPLATE = app



SOURCES += ./sources/main.cpp\
        ./sources/mainwindow.cpp \
    ./sources/stage.cpp \
    ./sources/contract.cpp \
    ./extra_widgets/monheaderwidget.cpp \
    ./extra_widgets/contractwidget.cpp \
    ./extra_widgets/stageprogresswidget.cpp \
    ./extra_widgets/stageredactor.cpp \
    ./extra_widgets/tablewidget.cpp \
    ./extra_widgets/contractredactordialog.cpp \
    sources/database.cpp

INCLUDEPATH += $$PWD/ $$PWD/headers/ $$PWD/extra_widgets/
HEADERS  += ./headers/mainwindow.h \
    ./headers/stage.h \
    ./headers/contract.h \
    ./extra_widgets/monheaderwidget.h \
    ./extra_widgets/contractwidget.h \
    ./extra_widgets/stageprogresswidget.h \
    ./extra_widgets/stageredactor.h \
    ./extra_widgets/tablewidget.h \
    ./extra_widgets/contractredactordialog.h \
    headers/database.h

FORMS    += ./forms/mainwindow.ui \
    ./extra_widgets/stageredactor.ui \
    ./extra_widgets/contractredactordialog.ui
   # ./extra_widgets/forms/monheaderwidget.ui \
    #extra_widgets/stagewidget.ui
