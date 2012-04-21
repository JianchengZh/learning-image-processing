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
    int rowNumber;
    int columnNumber;
    int colorDensity;

public:
    Image();

    // Getters
    int getRowNumber();
    int getColumnNumber();
    int getColorDensity();
    QString getImageType();

    // export
    virtual void exportar(QTextStream &fSalida) =0;
};

#endif // IMAGE_H
