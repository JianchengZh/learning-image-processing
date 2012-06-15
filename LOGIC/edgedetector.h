#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H
#include "basic.h"
#include "image.h"
#include "imagenpgm.h"
#define PI 3.14159265

class EdgeDetector : public Basic
{
public:
    EdgeDetector();
    Image *edgeDetectionSobel(Image *img, int position, int umbral);
    Image *edgeDetectorCanny(Image *img, int thresholdHigh, int thresholdsDown);
private:
    int discretDegree(double value);
    void nonMaximumSuppression(int height, int width,double **edgeNonMaximumSuppression, int** gradientOrientationDiscret, double**gradientMagnitude);
    void hysteresis(int height, int width,int**edgeHysteresis, double **edgeNonMaximumSuppression,int**gradientDegreeDiscret, int thresholdHigh, int thresholdsDown);
    int edgeFollow(int height, int width,int posX,int posY, int**edgeHysteresis, double **edgeNonMaximumSuppression,int**gradientDegreeDiscret,  int thresholdsDown);

};

#endif // EDGEDETECTOR_H
