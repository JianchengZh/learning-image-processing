//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: imagenpgm.h
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

#ifndef IMAGENPGM_H
#define IMAGENPGM_H


#include <QFile>
#include <math.h>
#include <QTextStream>
#include <QImage>
#include <QRgb>
#include <DATA_ACCESS/imagefile.h>
#include "image.h"

class ImagenPGM: public Image{

    int ***matrixImagenP;
    int *lut;

public:

    //Constructors
    ImagenPGM(QString filename);

    ImagenPGM(QString identification,
              QString coment,
              int h,
              int w,
              int colorD,
              int **matrix);

    ImagenPGM(QString identification,
              QString coment,
              int h,
              int w,
              int colorD,
              int ***matriz,
              int *lut);

    ~ImagenPGM();

    //Global Transformations
    Image *changeSize(int factor);
    Image *changeColorDepth(int bits);

    Image *average(ImagenPGM *qImage, double alpha);
    Image *add(ImagenPGM *qImage);
    Image *subtract(ImagenPGM *qImage);
    Image *multiply(ImagenPGM *qImage);
    Image *divide(ImagenPGM *qImage);


    Image *bimodalSegmentaion(int T);
    Image *histogramEqualization(int *newlut);

    // Getters
    int ***getMatrix();

    // GUI Display
    QImage *getQImage();

    //Histogram
    QImage *getHistogramImage();
    Histogram *getHistogram();

    // export
    void saveImage(QString filename);


};

#endif // IMAGENPGM_H
