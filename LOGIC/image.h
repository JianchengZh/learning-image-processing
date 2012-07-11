//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
//
// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@gmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@gmail.com
//
// Yerminson Doney Gonzalez         0843846-3743
// yermigon@gmail.com
//
// Edgar Andrés Moncada             0832294-3743
// edgarandres29@gmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************

#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QTextStream>
#include "histogram.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

    //SETTERS:
    void setImageIdentification(QString id);

    // Virtual Methods
    // export
    virtual void saveImage(QString filename) =0;

    // Image transformations
    virtual Image *changeSize(int factor)=0;
    virtual Image *changeColorDepth(int bits)=0;
    //virtual Image *equalizateHistogram(int *newlut)=0;
};

#endif // IMAGE_H
