//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: histogram.h
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

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "imagenpgm.h"

//

//
class Histogram
{
public:
    Histogram(ImagenPGM *imagen);
    ImagenPGM *getHistogram();
    int getMax1();
    int getMax2();

private:

    double *relativeFrecuency;
    int **matrizHistograma;
    int intensidad,totalNumberPixels ;
    int max1,max2,temp1,temp2;

    void generateMatrix();
    void calculateLocalMaximux();
    double findMaxRelativeFrecuency();

};
#endif
