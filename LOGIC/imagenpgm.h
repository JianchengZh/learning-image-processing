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

//#include <QList>
//#include <QString>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <QtAlgorithms>

#include <math.h>
#include <QTextStream>
#include "image.h"


class ImagenPGM: public Image{

    int ***matrixImagenP;
    int *lut;

public:

    ImagenPGM(QList<QString> lectura);

    ImagenPGM(QString identification,
              QString coment,
              int filas,
              int columnas,
              int colorD,
              int **matriz);

    ImagenPGM(QString identification,
              QString coment,
              int filas,
              int columnas,
              int colorD,
              int ***matriz,
              int *lut);

    //Image processing
    ImagenPGM changeIntensity(int bits);
    ImagenPGM changeSize(int factor);
    ImagenPGM *bimodalSegmentaion(int T);

    // Getters
    int ***getMatrix();

    // export
    void exportar(QTextStream &fSalida);


};

#endif // IMAGENPGM_H
