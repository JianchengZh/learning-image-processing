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

class Image
{

protected:

    QString identification;
    QString comment;
    QString imageType;
    int height;
    int width;
    int colorDepth;
    int lutSize;

public:
    Image();

    // Getters
    int getRowNumber();
    int getColumnNumber();
    int getColorDensity();
    QString getImageType();

    // export
    virtual void exportar(QString filename) =0;

    // Image transformations
    virtual Image *changeSize(int factor)=0;
    virtual Image *changeIntensity(int bits)=0;
};

#endif // IMAGE_H
