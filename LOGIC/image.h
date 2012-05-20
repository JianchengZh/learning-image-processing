//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: image.h
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

#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QTextStream>
#include "histogram.h"

class Image
{

protected:

    QString identification;
    QString imageType;
    int colorDepth;
    int height;
    int width;
    bool status;
    QImage *qImage;
    Histogram *histogram;

    virtual void generateHistogram()=0;
    virtual void generateQImage()=0;

public:
    Image();
    virtual ~Image();

    // GETTERS:
    QString getIdentification();
    QString getImageType();

    int getColorDepth();
    int getHeight();
    int getWidth();

    bool getStatus();

    Histogram *getHistogram();

    QImage *getQImage();
    QImage *getHistogramImage();

    // Virtual Methods
    // export
    virtual void saveImage(QString filename) =0;

    // Image transformations
    virtual Image *changeSize(int factor)=0;
    virtual Image *changeColorDepth(int bits)=0;
    //virtual Image *equalizateHistogram(int *newlut)=0;
};

#endif // IMAGE_H
