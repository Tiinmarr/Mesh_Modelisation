#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T10:55:17
#
#-------------------------------------------------

QT += core gui opengl widgets openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mesh_Computational_Geometry
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplaywidget.cpp \
    mesh.cpp

HEADERS  += mainwindow.h \
    gldisplaywidget.h \
    mesh.h

FORMS    += mainwindow.ui

#---- Comment the following line on MacOS
# LIBS = -lGLU

#---- Uncomment the following line on Windows
LIBS += -lglu32
LIBS += -lOpengl32

