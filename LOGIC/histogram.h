//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: histogram.h
// 
// FECHA: 11.07.12
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@gmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@gmail.com
//
// Yerminson Doney Gonzalez         0843846-3743
// yermigon@gmail.com
//
// Edgar Andrés Moncada             0832294-3743
// edgarandres29@gmail.com
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
        Histogram(int    height,
                  int    width,
                  int    colorD,
                  int ** matrix);

        ~Histogram();

        int ThresholdingByIsodata();
        int ThresholdingByOtsu();
        int ThresholdingByTwoPeaks();
        int * calculateEqualization();

        // Getters
        QImage * getHistogram();
        double * getColorFrequency();

    private:
        double * colorFrequency;
        int **   matrizHistograma;
        int      intensidad;
        double   u1, u2, w1, w2, n;
        QImage * qImage;

        void generateMatrix();
        double findMaxFrecuency();
        void calculatePromedio();
};
#endif


//~ Formatted by Jindent --- http://www.jindent.com
