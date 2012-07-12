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


#ifndef BASIC_H
#define BASIC_H

#include <math.h>
#include <qglobal.h>
#include <stdlib.h>

using namespace std;

class Basic
{
    public:
        Basic();

        int ** createKernelFilter(int * vectorKerneli,
                                  int * vectorKernelj,
                                  int   kernelSize);
        int ** applyKernel(int     height,
                           int     width,
                           int *** matrixImagenP,
                           int **  kernel,
                           int     kernelSizeX,
                           int     kernelSizeY);
        void applyKerneltoPixel(int *** matrixImagenP,
                                int     i,
                                int     j,
                                int **  kernel,
                                int     kernelSizeX,
                                int     kernelSizeY,
                                int **  matrix);
};
#endif // BASIC_H


//~ Formatted by Jindent --- http://www.jindent.com
