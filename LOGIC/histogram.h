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

class Histogram
{
public:
    Histogram(ImagenPGM *imagen);
    ~Histogram();

    int ThresholdingByIsodata();
    int ThresholdingByOtsu();
    int ThresholdingByTwoPeaks();
    int* calculateEqualization();

    //Getters
    ImagenPGM *getHistogram();

private:

    double *relativeFrecuency,*relativeEqualization;
    int **matrizHistograma;
    int intensidad, posicion;
    double u1,u2,w1,w2,n;

    void    generateMatrix();
    double  findMaxRelativeFrecuency();
    void    calculatePromedio();

};
#endif
