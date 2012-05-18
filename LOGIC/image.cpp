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

QString Image::getImageType(){
    return this->imageType;
}

bool Image::getStatus(){
    return this->status;
}

QString Image::getId(){
    return this->identification;
}

QString Image::getComment(){
    return this->comment;
}

int Image::getHeight(){
    return this->height;
}

int Image::getWidth(){
    return this->width;
}

int Image::getColorDepth(){
    return this->colorDepth
}
