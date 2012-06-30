#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "imagenpgm.h"

class Segmentation
{


private:
    int distance(int x, int y);
    bool equals(int *centroid, int *oldcentroid, int size);

public:
    Segmentation();
    Image* kmeans(Image* img, int clusters);







};

#endif // SEGMENTATION_H
