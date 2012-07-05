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

#ifndef IMAGENPPM_H
#define IMAGENPPM_H

#include "imagenpgm.h"
#include "image.h"
#include <QImage>
#include <QRgb>
using namespace std;

class ImagenPPM: public Image
{
    int ***matrixRp, ***matrixGp, ***matrixBp;
    int *lutR, *lutG, *lutB;

    void generateHistogram();
    void generateQImage();
public:

    //Constructors
    ImagenPPM(QString filename);

    ImagenPPM(QString id,
              int h,
              int w,
              int depth,
              int **matrizR,
              int **matrizG,
              int **matrizB);

    ImagenPPM(QString id,
              int h,
              int w,
              int colorD,
              int ***matrizR,
              int *lutR,
              int ***matrizG,
              int *lutG,
              int ***matrizB,
              int *lutB);

    ~ImagenPPM();

    //Image processing
    Image* changeSize(int factor);
    Image* changeColorDepth(int bits);
    ImagenPGM* convertToGrayScale(int method);
    //   Image *equalizateHistogram(int *newlut);

    // Getters
    int ***getMatrizR();
    int ***getMatrizG();
    int ***getMatrizB();

    // Export
    void saveImage(QString filename);
};

#endif // IMAGENPPGM_H
