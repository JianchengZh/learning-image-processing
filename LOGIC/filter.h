#ifndef FILTER_H
#define FILTER_H
#include "imagenpgm.h"
#include "basic.h"

class Filter : public Basic
{
public:
    Filter();
    Image* meanFilter(Image* img, int kernelSize);
    Image* convolutionFilter(Image* img,int **kernel,int kernelSize);
    Image* gaussianaFilter(Image* img, int sigma, int kernelSize);
    Image *noiseCleaningPixel(Image* img, int delta);
    Image * noiseCleaningLine(Image *img, int delta);
};

#endif // FILTER_H
