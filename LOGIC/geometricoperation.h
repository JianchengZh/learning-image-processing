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



#ifndef GEOMETRICOPERATION_H
#define GEOMETRICOPERATION_H

#include "basic.h"
#include "imagenpgm.h"

class GeometricOperation:
    public Basic
{
    private:
        int * multiplyVectorMatrix(int *     vector,
                                   double ** matriz);

    public:
        enum axis { Y, X };

        GeometricOperation();

        Image * scaling(Image * img,
                        double  factorX,
                        double  factorY);
        Image * translation(Image * img,
                            double  factorX,
                            double  factorY);
        Image * rotation(Image * img,
                         double  angle);
        Image * reflection(Image * img,
                           axis    orientation);
};
#endif // GEOMETRICOPERATION_H


//~ Formatted by Jindent --- http://www.jindent.com
