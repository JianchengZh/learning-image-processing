#-------------------------------------------------
#
# Project created by QtCreator 2012-03-10T00:20:53
#
#-------------------------------------------------

QT       += core gui

TARGET = LEARNING_IMAGE_PROCESSING
TEMPLATE = app


SOURCES += main.cpp\
    GUI/mainwindow.cpp \
    GUI/dialogabout.cpp \
    LOGIC/histogram.cpp \
    LOGIC/imagenpgm.cpp \
    LOGIC/imagenppm.cpp \
    CONTROLLER/maincontroller.cpp \
    DATA_ACCESS/imagefile.cpp \
    LOGIC/image.cpp \
    GUI/resizeqwidget.cpp \
    GUI/colordepthqwidget.cpp

HEADERS  += \
    GUI/mainwindow.h \
    GUI/dialogabout.h \
    LOGIC/histogram.h \
    LOGIC/imagenpgm.h \
    LOGIC/imagenppm.h \
    CONTROLLER/maincontroller.h \
    DATA_ACCESS/imagefile.h \
    LOGIC/image.h \
    GUI/resizeqwidget.h \
    GUI/colordepthqwidget.h

FORMS    += \
    GUI/dialogabout.ui \
    GUI/mainwindow.ui \
    GUI/resizeqwidget.ui \
    GUI/colordepthqwidget.ui

#QMAKE_CXXFLAGS += -DHAVE_CONFIG_H

#unix:!macx:!symbian: LIBS += -ldcmimgle
#unix:!macx:!symbian: LIBS += -ldcmdata
#unix:!macx:!symbian: LIBS += -loflog
#unix:!macx:!symbian: LIBS += -lofstd
