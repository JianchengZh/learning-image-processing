#ifndef GLOBALTRANSFORMATION_H
#define GLOBALTRANSFORMATION_H

#include "basic.h"
#include "imagenpgm.h"

class GlobalTransformation : public Basic
{



public:
    enum binaryOperation{And, Or, Xor};
    enum unaryOperation{Not};

    GlobalTransformation();
    Image *binaryOperations(Image *image1, Image *image2, binaryOperation operation );
    Image *unaryOperations(Image *image1,unaryOperation operation);


    Image *average(Image* img, Image *image, double alpha);
    Image *add(Image* img, Image *image);
    Image *subtract(Image* img, Image *image);
    Image *multiply(Image* img, Image *image);
    Image *divide(Image* img, Image *image);





};

#endif // GLOBALTRANSFORMATION_H
