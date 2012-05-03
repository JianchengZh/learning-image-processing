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
#include "image.h"


class ImagenPGM: public Image{

    int ***matrixImagenP;
    int *lut;

public:

    //Constructors
    ImagenPGM(QList<QString> lectura);

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
              int *lut,
              int lutSize);

    ~ImagenPGM();

    //Image processing
    Image *changeSize(int factor);
    Image *changeColorDepth(int bits);
    Image *bimodalSegmentaion(int T);

    // Getters
    int ***getMatrix();

    // export
    void exportar(QString filename);


};

#endif // IMAGENPGM_H
