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
    ~Histogram();

    ImagenPGM *getHistogram();

    //Getters
    int getMax1();
    int getMax2();
    int calculateThresholdIsodata();
    int calculateThresholdOtsu();
    void calculateTwoPeaks();
    int* calculeEqualization();

private:

    double *relativeFrecuency,*relativeEqualization;
    int **matrizHistograma;
    int intensidad, posicion;
    int max1,max2,umbral;
    double u1,u2,w1,w2,n;

    void generateMatrix();
    double findMaxRelativeFrecuency();
    void calculatePromedio();

};
#endif
