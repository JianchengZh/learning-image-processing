//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: image.cpp
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

#ifndef IMAGENDCM_H
#define IMAGENDCM_H

#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "LOGIC/image.h"
#include <QFile>
#include <QTextStream>
#include <math.h>
#include <QImage>
#include <QRgb>


class ImagenDCM : public Image{

    DicomImage *dicomImage;
    int ***matrixImagenP;
    int *lut;

public:

    ImagenDCM(const char *fileName);
    Image *changeSize(int factor);
    Image *changeColorDepth(int bits);

    // export
    void saveImage(QString filename);

    // GUI Display
    QImage *getQImage();
};

#endif // IMAGENDCM_H
