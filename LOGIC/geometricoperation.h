#ifndef GEOMETRICOPERATION_H
#define GEOMETRICOPERATION_H
#include "basic.h"
#include "imagenpgm.h"
class GeometricOperation : public Basic
{
public:
    GeometricOperation();
    Image *average(Image* img, Image *image, double alpha);
    Image *add(Image* img, Image *image);
    Image *subtract(Image* img, Image *image);
    Image *multiply(Image* img, Image *image);
    Image *divide(Image* img, Image *image);
};

#endif // GEOMETRICOPERATION_H
