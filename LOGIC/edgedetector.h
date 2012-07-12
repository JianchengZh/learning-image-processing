//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
//
// FECHA INICIACION: Marzo de 2012
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


#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H

#include "basic.h"
#include "image.h"
#include "imagenpgm.h"

#define PI 3.14159265
class EdgeDetector:
    public Basic
{
    public:
        EdgeDetector();

        Image * edgeDetectionSobel(Image * img,
                                   int     position,
                                   int     umbral);
        Image * edgeDetectorCanny(Image * img,
                                  int     thresholdHigh,
                                  int     thresholdsDown);

    private:
        int discretDegree(double value);
        void nonMaximumSuppression();
        void hysteresis(int thresholdHigh,
                        int thresholdsDown);
        int edgeFollow(int posX,
                       int posY,
                       int thresholdsDown);

        int       height;
        int       width;
        int       colorDepth;
        int ***   matrixImagenP;
        double ** gradientMagnitude;
        int **    gradientDegreeDiscret;
        double ** edgeNonMaximumSuppression;
        int **    edgeHysteresis;
};
#endif // EDGEDETECTOR_H


//~ Formatted by Jindent --- http://www.jindent.com
