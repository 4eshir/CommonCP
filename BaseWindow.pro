#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T18:34:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaseWindow
TEMPLATE = app


SOURCES += main.cpp\
        basewindow.cpp \
    theory.cpp \
    abstractview.cpp \
    task1lcs.cpp \
    task1view.cpp \
    task2matrix.cpp \
    task2view.cpp \
    task3knapsack.cpp \
    task3view.cpp \
    demo.cpp \
    test.cpp \
    questions.cpp \
    identification.cpp \
    help.cpp

HEADERS  += basewindow.h \
    theory.h \
    abstracttask.h \
    abstractview.h \
    exceptions.h \
    task1lcs.h \
    task1view.h \
    task2matrix.h \
    task2view.h \
    task3knapsack.h \
    task3view.h \
    demo.h \
    test.h \
    questions.h \
    identification.h \
    help.h

FORMS    +=

SUBDIRS += \
    ../Theory/theoryPart/theoryPart.pro \
    ../Theory/theoryPart/theoryPart.pro
