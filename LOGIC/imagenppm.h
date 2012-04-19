//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: imagenppm.h
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

#ifndef IMAGENPPM_H
#define IMAGENPPM_H

//#include <QList>
//#include <QString>
//#include <QTextStream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <QtAlgorithms>
//#include <math.h>
#include "imagenpgm.h"
#include "image.h"

class ImagenPPM: public Image
{
//    QString identificacion, comentario;
//    int rowNumber, columnNumber, intensity;
    int **matrizR, **matrizG, **matrizB;

public:

    ImagenPPM(QList<QString> lectura);
    ImagenPPM(QString id,
              QString coment,
              int filas,
              int columnas,
              int intensity,
              int **matrizR,
              int **matrizG,
              int **matrizB);

//    int getRowNumber();
//    int getColumnNumber();
//    int getColorDensity();

    void exportar(QTextStream &fSalida);
    ImagenPPM *reducirTamano();
    ImagenPPM *reducirIntensidad(int bits);
    ImagenPGM *convertirGris(int opcion);
};

#endif // IMAGENPPGM_H
