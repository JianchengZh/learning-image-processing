//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: image.cpp
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

#include "image.h"

Image::Image()
{
}

Image::~Image(){
}

QString Image::getIdentification(){
    return this->identification;
}

QString Image::getImageType(){
    return this->imageType;
}

int Image::getHeight(){
    return this->height;
}

int Image::getWidth(){
    return this->width;
}

int Image::getColorDepth(){
    return this->colorDepth;
}

bool Image::getStatus(){
    return this->status;
}

Histogram* Image::getHistogram(){
    return this->histogram;
}

QImage* Image::getQImage(){
    return this->qImage;
}

QImage* Image::getHistogramImage(){
    return this->histogram->getHistogram();
}

