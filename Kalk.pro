#-------------------------------------------------
#
# Project created by QtCreator 2018-06-25T11:54:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kalk
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Ipergeometrica.cpp \
    Bernoulli.cpp \
    Binomiale.cpp \
    Geometrica.cpp \
    Pascal.cpp \
    Poisson.cpp \
    Skellam.cpp \
    CustomException.cpp \
    Controller.cpp

HEADERS  += mainwindow.h \
    VariabileAleatoria.h \
    Ipergeometrica.h \
    Bernoulli.h \
    Binomiale.h \
    Geometrica.h \
    Pascal.h \
    Poisson.h \
    Skellam.h \
    CustomException.h \
    Controller.h

FORMS    += mainwindow.ui
