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



    Image *scaling(Image *img, double factorX, double factorY);







};

#endif // GEOMETRICOPERATION_H
