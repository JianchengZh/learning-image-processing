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
    int colorDepth;
    int height;
    int width;
    bool status;
    QImage *qImage;

public:
    Image();
    virtual ~Image();


    // Getters
    QString getImageType();
    bool getStatus();
    QString getId();
    QString getComment();
    int getHeight();
    int getWidth();
    int getColorDepth();
    virtual QImage* getQImage()=0;


    // export
    virtual void saveImage(QString filename) =0;

    // Image transformations
    virtual Image *changeSize(int factor)=0;
    virtual Image *changeColorDepth(int bits)=0;
    //virtual Image *equalizateHistogram(int *newlut)=0;
};

#endif // IMAGE_H
