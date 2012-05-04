//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: maincontroller.h
//
// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@hotmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@hotmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

// Qt include
#include <QImage>
//#include <QString>

// Project include
#include "LOGIC/imagenpgm.h"
#include "LOGIC/imagenppm.h"
#include "LOGIC/image.h"
#include "LOGIC/histogram.h"
#include "DATA_ACCESS/imagefile.h"

class MainController
{
private:

    Image *imagen, *oldImage;
    QImage *displayedImage, *oldDisplayedImage;
    Histogram *histogram;

public:

    MainController();
    ~MainController();

    bool loadImage(QString filename);
    QImage *generateHistogram();

    // Image Processing:
    bool changeSize(int density);
    bool changeColorDepth(int depth);
    bool bimodalSegmentaion(int T);
    void convertToGrayscale(int method);
    bool isodataSegmentation();


    // Getters:
    Image *getImage();
    QImage *getQImage();

    // Others methods:
    bool undo();

};
#endif // MAINCONTROLLER_H
