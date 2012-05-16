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
#include "LOGIC/imagendcm.h"
#include "LOGIC/image.h"
#include "LOGIC/histogram.h"
#include "DATA_ACCESS/imagefile.h"

class MainController
{
private:

    Image *imagen, *oldImage;
    QImage *displayedImage, *oldDisplayedImage;
    Histogram *histogram, *oldHistogram;

public:

    MainController();
    ~MainController();

    bool loadImage(QString filename);


    // Global Transformations
    void changeSize(int density);
    void changeColorDepth(int depth);
    void convertToGrayscale(int method);
    bool add(QString filename, double alpha);

    bool bimodalSegmentaion(int T);
    bool equalizateHistogram();
    void otsuSegmentation();
    void isodataSegmentation();

    // Getters:
    Image *getImage();
    QImage *getQImage();
    QImage *getHistogramImage();

    // Others methods:
    bool undo();
    bool isThereAnUploadedImage();
    void saveImage(QString filename);

};
#endif // MAINCONTROLLER_H
