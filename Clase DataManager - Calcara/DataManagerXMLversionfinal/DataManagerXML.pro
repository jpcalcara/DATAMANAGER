#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T00:03:33
#
#-------------------------------------------------

QT       += core gui
QT       += widgets xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataManagerXML
TEMPLATE = app


SOURCES += main.cpp\
        ventana.cpp \
    datamanager.cpp

HEADERS  += ventana.h \
    datamanager.h

FORMS    += ventana.ui
