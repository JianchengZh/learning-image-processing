//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: imagefile.h
//
// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@hotmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@hotmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************

#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>


#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

class ImageFile: public QFile
{
private:
    QList<QString> lectura;
    QList<QString> supportedFormats;
    QString id;
    int colorDepth;
    int height;
    int width;
    int *matrix;


public:
    ImageFile(QString fileName);
    bool readFile();
    bool readFileImage();
    void readingProcess();
    void printImageContents();
    QList<QString> getImageContents();

    //GETTERS
    QString getId();
    int getColorDepth();
    int getHeight();
    int getWidth();
    int *getMatrix();
};

#endif // IMAGEFILE_H
