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



#ifndef GLOBALTRANSFORMATION_H
#define GLOBALTRANSFORMATION_H

#include "basic.h"
#include "imagenpgm.h"
#include <algorithm>

class GlobalTransformation:
    public Basic
{
    public:
        enum binaryOperation { And, Or, Xor };

        enum unaryOperation { Not };

        GlobalTransformation();

        Image * binaryOperations(Image *         image1,
                                 Image *         image2,
                                 binaryOperation operation);
        Image * unaryOperations(Image *        image1,
                                unaryOperation operation);
        Image * average(Image * img,
                        Image * image,
                        double  alpha);
        Image * add(Image * img,
                    Image * image);
        Image * subtract(Image * img,
                         Image * image);
        Image * multiply(Image * img,
                         Image * image);
        Image * divide(Image * img,
                       Image * image);
        Image * maxOp(Image * img,
                      Image * image);
        Image * minOp(Image * img,
                      Image * image);
};
#endif // GLOBALTRANSFORMATION_H


//~ Formatted by Jindent --- http://www.jindent.com
