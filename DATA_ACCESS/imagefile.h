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

    bool readFileImage();


public:
    ImageFile(QString fileName);
    bool readFile();

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
