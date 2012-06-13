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

#include <QImage>
#include "math.h"

class Histogram
{
public:
    Histogram(int height, int width, int colorD, int **matrix);
    ~Histogram();

    int ThresholdingByIsodata();
    int ThresholdingByOtsu();
    int ThresholdingByTwoPeaks();
    int* calculateEqualization();

    //Getters
    QImage *getHistogram();
    double *getColorFrequency();

private:

    double *colorFrequency;
    int **matrizHistograma;
    int intensidad;
    double u1,u2,w1,w2,n;
    QImage *qImage;


    void    generateMatrix();
    double  findMaxFrecuency();
    void    calculatePromedio();

};
#endif
