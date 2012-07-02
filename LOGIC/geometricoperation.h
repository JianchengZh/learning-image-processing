#ifndef GEOMETRICOPERATION_H
#define GEOMETRICOPERATION_H
#include "basic.h"
#include "imagenpgm.h"
class GeometricOperation : public Basic
{

private:
    int *multiplyVectorMatrix(int *vector,double **matriz);

public:
    GeometricOperation();
    Image *average(Image* img, Image *image, double alpha);
    Image *add(Image* img, Image *image);
    Image *subtract(Image* img, Image *image);
    Image *multiply(Image* img, Image *image);
    Image *divide(Image* img, Image *image);



    Image *scaling(Image *img, double factorX, double factorY);







};

#endif // GEOMETRICOPERATION_H
