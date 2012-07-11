//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: segmentation.h
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



#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "imagenpgm.h"
#include "imagenppm.h"

struct color
{
    int r;
    int g;
    int b;
};


typedef struct color color;


class Segmentation
{
    private:
        int distanceGray(int x,
                         int y);
        int distanceColor(color a,
                          color b);
        bool equalsGray(int * centroid,
                        int * oldcentroid,
                        int   size);
        bool equalsColor(color * centroid,
                         color * oldcentroid,
                         int     size);
        color getColor(Image * img,
                       int     x,
                       int     y);

    public:
        Segmentation();

        Image * kmeansPGM(Image * img,
                          int     clusters);
        Image * kmeansPPM(Image * img,
                          int     clusters);
        Image * removeCap(Image * img);
        Image * whiteTissue(Image * img);
        Image * grayTissue(Image * img);
};
#endif // SEGMENTATION_H


//~ Formatted by Jindent --- http://www.jindent.com
