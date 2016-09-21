#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T22:28:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Archive
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    dialog_zip.cpp \
    dialog_unzip.cpp \
    dialog_pros.cpp \
    union.cpp \
    zip.cpp \
    creating_nodes.cpp \
    ununion.cpp \
    unzip.cpp

HEADERS  += dialog.h \
    dialog_zip.h \
    dialog_unzip.h \
    dialog_pros.h \
    main.h \
    union.h \
    creating_nodes.h \
    zip.h \
    ununion.h \
    unzip.h

FORMS    += dialog.ui \
    dialog_zip.ui \
    dialog_unzip.ui \
    dialog_pros.ui

CONFIG+=c++11
