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

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

// Qt include
#include <QImage>
//#include <QString>

// Project include
#include "LOGIC/imagenpgm.h"
#include "LOGIC/imagenppm.h"
#include "LOGIC/imagendcm.h"
#include "LOGIC/image.h"
#include "LOGIC/histogram.h"
#include "DATA_ACCESS/imagefile.h"
#include "LOGIC/edgedetector.h"
#include "LOGIC/segmentation.h"

class MainController
{
private:

    Image *imagen, *oldImage;

public:

    MainController();
    ~MainController();

    bool loadImage(QString filename);


    // Global Transformations
    void changeSize(int density);
    void changeColorDepth(int depth);
    void convertToGrayscale(int method);
    bool average(QString filename, double alpha);
    bool add(QString filename);
    bool subtract(QString filename);
    bool multiply(QString filename);
    bool divide(QString filename);

    bool bimodalSegmentaion(int T);
    void equalizateHistogram();
    void otsuSegmentation();
    void isodataSegmentation();

    //contrast
    void gammaCorrection(double r);
    void contrastStretching();

    //Filter
    void meanFilter(int size);
    void convolutionFilter(int **kernel, int size);
    void gaussianaFilter(int size);
    void noiseCleaningPixel(int delta);
    void noiseCleaningLine(double delta);

    //Edge Detection
    void edgeDetectionSobel(int position);
    void edgeDetectorCanny(int thresholdHigh, int thresholdDown);

    //Segementation
    void segmentationK_Means(int cluster);

    // DICOM
    void applyWindowLevel(int window, int level);

    // Getters:
    Image *getImage();
    QImage *getQImage();
    QImage *getHistogramImage();

    // Others methods:
    bool undo();
    bool isThereAnUploadedImage();
    void saveImage(QString filename);

};
#endif // MAINCONTROLLER_H
