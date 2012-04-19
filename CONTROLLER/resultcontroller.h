//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: resultcontroller.h
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

#ifndef RESULTCONTROLLER_H
#define RESULTCONTROLLER_H

#include <QString>
#include "LOGIC/imagenpgm.h"
#include "LOGIC/imagenppm.h"
#include "DATA_ACCESS/imagefile.h"

class ResultController
{

private:
    ImagenPGM *imagenPGM;
    ImagenPPM *imagenPPM;
    QString imageType;

public:
    ResultController(QString temImageFile);
    void saveImage(QString fileNameDest);
};

#endif // RESULTCONTROLLER_H
