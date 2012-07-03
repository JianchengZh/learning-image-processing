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
    GUI/colordepthqwidget.cpp \
    GUI/thresholdqwidget.cpp \
    LOGIC/imagendcm.cpp \
    GUI/windowlevelqwidget.cpp \
    GUI/convolutionqwidget.cpp \
    GUI/customqlabel.cpp \
    GUI/sobelqwidget.cpp \
    LOGIC/filter.cpp \
    LOGIC/edgedetector.cpp \
    LOGIC/geometricoperation.cpp \
    LOGIC/globaltransformation.cpp \
    LOGIC/basic.cpp \
    LOGIC/segmentation.cpp \
    GUI/cannywidget.cpp

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
    GUI/colordepthqwidget.h \
    GUI/thresholdqwidget.h \
    LOGIC/imagendcm.h \
    GUI/windowlevelqwidget.h \
    GUI/convolutionqwidget.h \
    GUI/customqlabel.h \
    GUI/sobelqwidget.h \
    LOGIC/filter.h \
    LOGIC/edgedetector.h \
    LOGIC/geometricoperation.h \
    LOGIC/globaltransformation.h \
    LOGIC/basic.h \
    LOGIC/segmentation.h \
    GUI/cannywidget.h

FORMS    += \
    GUI/dialogabout.ui \
    GUI/mainwindow.ui \
    GUI/resizeqwidget.ui \
    GUI/colordepthqwidget.ui \
    GUI/thresholdqwidget.ui \
    GUI/windowlevelqwidget.ui \
    GUI/convolutionqwidget.ui \
    GUI/sobelqwidget.ui \
    GUI/cannywidget.ui
    

QMAKE_CXXFLAGS += -DHAVE_CONFIG_H

unix:!macx:!symbian: LIBS += -ldcmimgle
unix:!macx:!symbian: LIBS += -ldcmdata
unix:!macx:!symbian: LIBS += -loflog
unix:!macx:!symbian: LIBS += -lofstd

OTHER_FILES += \
    GUI/UNIVALLE.ppm
