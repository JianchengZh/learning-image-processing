#ifndef GEOMETRICOPERATION_H
#define GEOMETRICOPERATION_H
#include "basic.h"
#include "imagenpgm.h"
class GeometricOperation : public Basic
{

private:
    int *multiplyVectorMatrix(int *vector,double **matriz);

public:
    enum axis{Y,X};
    GeometricOperation();
    Image *scaling(Image *img, double factorX, double factorY);
    Image *translation(Image *img, double factorX, double factorY);
    Image *rotation(Image *img, double angle);
    Image *reflection(Image *img, axis orientation);

};

#endif // GEOMETRICOPERATION_H
