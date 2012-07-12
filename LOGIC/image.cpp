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



#include "image.h"

Image::Image()
{
}

Image::~Image()
{
}

QString Image::getIdentification()
{
    return this -> identification;
}

QString Image::getImageType()
{
    return this -> imageType;
}

int Image::getHeight()
{
    return this -> height;
}

int Image::getWidth()
{
    return this -> width;
}

int Image::getColorDepth()
{
    return this -> colorDepth;
}

bool Image::getStatus()
{
    return this -> status;
}

Histogram * Image::getHistogram()
{
    return this -> histogram;
}

QImage * Image::getQImage()
{
    return this -> qImage;
}

QImage * Image::getHistogramImage()
{
    return this -> histogram -> getHistogram();
}

void Image::setImageIdentification(QString id)
{
    this -> identification = id;
}


//~ Formatted by Jindent --- http://www.jindent.com
