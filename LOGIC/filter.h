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



#ifndef FILTER_H
#define FILTER_H

#include "imagenpgm.h"
#include "basic.h"

class Filter:
    public Basic
{
    public:
        Filter();

        Image * meanFilter(Image * img,
                           int     kernelSize);
        Image * convolutionFilter(Image * img,
                                  int **  kernel,
                                  int     kernelSize);
        Image * gaussianaFilter(Image * img,
                                int     kernelSize);
        Image * noiseCleaningPixel(Image * img,
                                   int     delta);
        Image * noiseCleaningLine(Image * img,
                                  int     delta);
};
#endif // FILTER_H


//~ Formatted by Jindent --- http://www.jindent.com
