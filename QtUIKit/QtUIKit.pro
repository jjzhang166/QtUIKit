#-------------------------------------------------
#
# Project created by QtCreator 2016-12-09T13:38:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtUIKit
TEMPLATE = app


SOURCES += main.cpp\
        CustomMainWidget.cpp \
    BaseWidget/AutoSizeWidget.cpp \
    BaseWidget/UIMainView.cpp \
    BaseWidget/BaseMenu/BaseMenu.cpp

HEADERS  += CustomMainWidget.h \
    BaseWidget/AutoSizeWidget.h \
    BaseWidget/ImportHeaderFile.h \
    BaseWidget/UIMainView.h \
    BaseWidget/BaseMenu/BaseMenu.h
