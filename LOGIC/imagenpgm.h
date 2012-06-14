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

#ifndef IMAGENPGM_H
#define IMAGENPGM_H


#include <QFile>
#include <math.h>
#include <QTextStream>
#include <QImage>
#include <QRgb>
#include <DATA_ACCESS/imagefile.h>
#include "image.h"
using namespace std;

#define PI 3.14159265
class ImagenPGM: public Image{

    int ***matrixImagenP;
    int *lut;
    int** resultMatrixI;
    int** resultMatrixJ;

    void generateHistogram();
    void generateQImage();
    int **applyKernel(int** kernel,int kernelSizeX, int kernelSizeY);
    void applyKerneltoPixel(int i,int j,int **kernel, int kernelSizeX, int kernelSizeY, int **matrix);
    Image *clasify(int* centroid, int size , int iterations);
    int **matrizMagnitud(int umbral);

public:

    //Constructors
    ImagenPGM(QString filename);

    ImagenPGM(int h,
              int w,
              int colorD,
              int **matrix);

    ImagenPGM(int h,
              int w,
              int colorD,
              int ***matrixP,
              int *lut);

    ~ImagenPGM();

    //Global Transformations
    Image *changeSize(int factor);
    Image *changeColorDepth(int bits);

    Image *average(ImagenPGM *qImage, double alpha);
    Image *add(ImagenPGM *qImage);
    Image *subtract(ImagenPGM *qImage);
    Image *multiply(ImagenPGM *qImage);
    Image *divide(ImagenPGM *qImage);

    Image *bimodalSegmentaion(int T);
    Image *histogramEqualization(int *newlut);

    //Contrast
    Image *gammaCorrection(double r);
    Image *contrastStretching();

    //Segmentation
    Image *kmeans(int clusters, int iterations);

    //Filters
    Image *meanFilter(int kernelSize);
    Image *convolutionFilter(int **kernel,int kernelSize);
    int **createKernelFilter(int *vectorKerneli, int *vectorKernelj, int kernelSize);
    Image *gaussianaFilter(int sigma, int kernelSize);
    Image *noiseCleaningPixel(int delta);
    Image *noiseCleaningLine(int delta);

    //Edge Detection
    Image *edgeDetectionSobel(int position, int umbral);
    Image *edgeDetectorCanny(int thresholdHigh, int thresholdsDown);
private:
    int discretDegree(double value);
    void nonMaximumSuppression(double **edgeNonMaximumSuppression, int** gradientOrientationDiscret, double**gradientMagnitude);
    void hysteresis(int**edgeHysteresis, double **edgeNonMaximumSuppression,int**gradientDegreeDiscret, int thresholdHigh, int thresholdsDown);
    int edgeFollow(int posX,int posY, int**edgeHysteresis, double **edgeNonMaximumSuppression,int**gradientDegreeDiscret,  int thresholdsDown);
public:
    // Getters
    int ***getMatrix();

    // export
    void saveImage(QString filename);
};

#endif // IMAGENPGM_H
