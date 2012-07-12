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


#ifndef IMAGENDCM_H
#define IMAGENDCM_H

#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "LOGIC/image.h"
#include <QFile>
#include <QTextStream>
#include <math.h>
#include <QImage>
#include <QRgb>
#include <QDebug>
#include <QPoint>
#include <iostream>
#include <QStringList>

using namespace std;

class ImagenDCM:
        public Image
{

    int ***       matrixImagenP;
    int *         lut;
    int           lutSize;
    double        minDensity, maxDensity;
    double        distanceTomography;

    OFString      pixelSpacing;
    DicomImage *  dicomImage;
    DicomImage *  firstImage;

    DcmFileFormat fileformat;
    OFCondition   statusDcmFileFormat;

    void generateHistogram();
    void generateQImage();

    int getDensity(int x, int y);
    int appyCalibrationFunction(int pixelValue, int rescaleSlope, int rescaleIntercept);
    int pixelWindowLevel(int pixelValue,int window,int center);

public:

    ImagenDCM(const char * fileName);

    QString getDataSet();
    double getDistanceTomography(QPoint start, QPoint end);
    void applyWindowLevel(int window, int level);
    void setFrameImage(int frame);

    // VIRTUAL METHODS
    Image * changeSize(int factor);
    Image * changeColorDepth(int bits);

    // SETTERS:
    void resetDistanceTomography();

    // GETTERS:
    int     getCountFrameFirstImage();
    double  getDistanceTomography();
    int *** getMatrixImagenP();
    int *   getLut();

    // SAVE IMAGE
    void saveImage(QString filename);
};
#endif // IMAGENDCM_H
