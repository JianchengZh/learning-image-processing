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

#include "customqlabel.h"

CustomQLabel::CustomQLabel(QWidget *parent) :
    QLabel(parent)
{
    startPoint = QPoint(-1,-1);
    setMouseTracking(true);
}

void CustomQLabel::mousePressEvent(QMouseEvent *event){

    startPoint= QPoint(event->x(), event->y());
    if (this->pixmap()!=0) {
        emit eraseLine();
    }
}

void CustomQLabel::mouseMoveEvent(QMouseEvent *event){

    endPoint= QPoint(event->x(), event->y());
    emit mousePosition(endPoint);
    if (this->pixmap()!=0 && startPoint!= QPoint(-1,-1)) {
        emit eraseLine();
        emit drawLine(startPoint, endPoint);
    }

}

void CustomQLabel::mouseReleaseEvent(QMouseEvent *event){

    endPoint= QPoint(event->x(), event->y());

    if (this->pixmap()!=0) {
        emit drawLine(startPoint, endPoint);
    }

}
