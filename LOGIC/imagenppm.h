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

#include "imagenpgm.h"
#include "image.h"

class ImagenPPM: public Image
{
    int **matrizR, **matrizG, **matrizB;

public:

    //Constructors
    ImagenPPM(QList<QString> lectura);
    ImagenPPM(QString id,
              QString coment,
              int filas,
              int columnas,
              int intensity,
              int **matrizR,
              int **matrizG,
              int **matrizB);

    //Image processing
    Image *changeSize(int factor);
    //    ImagenPPM *reducirTamano();
    //    ImagenPPM *reducirIntensidad(int bits);
    //    ImagenPGM *convertirGris(int opcion);

    // Getters

    // export
    void exportar(QString filename);
};

#endif // IMAGENPPGM_H
