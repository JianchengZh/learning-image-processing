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
//#include <QImage>
//#include <QString>

// Project include
#include "LOGIC/imagenpgm.h"
#include "LOGIC/imagenppm.h"
#include "LOGIC/image.h"
#include "LOGIC/histogram.h"
#include "DATA_ACCESS/imagefile.h"
#include "LOGIC/imagedcm.h"

class MainController
{
private:

    ImagenPGM *imagenPGM;
    ImagenPPM *imagenPPM;
    Image *imagen;
    QImage *qImage;

    void exportTempImage(Image *imagen, QString filename);

public:

    MainController();
    ~MainController();

    bool loadImage(QString filename);
    QString pixelDensityChanged(int density);
    QString colorDensityChanged(int intensidad);
    QString convertGrayscale();
    QImage *generateHistogram();
    void newJob();

    // Getters
    Image *getImage();

};
#endif // MAINCONTROLLER_H
